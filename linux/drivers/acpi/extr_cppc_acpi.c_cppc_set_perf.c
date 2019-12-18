#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cppc_perf_ctrls {int /*<<< orphan*/  desired_perf; } ;
struct cppc_pcc_data {int pending_pcc_write_cmd; scalar_t__ pcc_write_cnt; int /*<<< orphan*/  pcc_write_wait_q; int /*<<< orphan*/  pcc_lock; scalar_t__ platform_owns_pcc; } ;
struct cpc_register_resource {int dummy; } ;
struct cpc_desc {scalar_t__ write_cmd_id; int write_cmd_status; struct cpc_register_resource* cpc_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_WRITE ; 
 scalar_t__ CPC_IN_PCC (struct cpc_register_resource*) ; 
 size_t DESIRED_PERF ; 
 int ENODEV ; 
 int check_pcc_chan (int,int) ; 
 int /*<<< orphan*/  cpc_desc_ptr ; 
 int /*<<< orphan*/  cpc_write (int,struct cpc_register_resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_pcc_subspace_idx ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ down_write_trylock (int /*<<< orphan*/ *) ; 
 struct cppc_pcc_data** pcc_data ; 
 struct cpc_desc* per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  send_pcc_cmd (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int cppc_set_perf(int cpu, struct cppc_perf_ctrls *perf_ctrls)
{
	struct cpc_desc *cpc_desc = per_cpu(cpc_desc_ptr, cpu);
	struct cpc_register_resource *desired_reg;
	int pcc_ss_id = per_cpu(cpu_pcc_subspace_idx, cpu);
	struct cppc_pcc_data *pcc_ss_data = NULL;
	int ret = 0;

	if (!cpc_desc) {
		pr_debug("No CPC descriptor for CPU:%d\n", cpu);
		return -ENODEV;
	}

	desired_reg = &cpc_desc->cpc_regs[DESIRED_PERF];

	/*
	 * This is Phase-I where we want to write to CPC registers
	 * -> We want all CPUs to be able to execute this phase in parallel
	 *
	 * Since read_lock can be acquired by multiple CPUs simultaneously we
	 * achieve that goal here
	 */
	if (CPC_IN_PCC(desired_reg)) {
		if (pcc_ss_id < 0) {
			pr_debug("Invalid pcc_ss_id\n");
			return -ENODEV;
		}
		pcc_ss_data = pcc_data[pcc_ss_id];
		down_read(&pcc_ss_data->pcc_lock); /* BEGIN Phase-I */
		if (pcc_ss_data->platform_owns_pcc) {
			ret = check_pcc_chan(pcc_ss_id, false);
			if (ret) {
				up_read(&pcc_ss_data->pcc_lock);
				return ret;
			}
		}
		/*
		 * Update the pending_write to make sure a PCC CMD_READ will not
		 * arrive and steal the channel during the switch to write lock
		 */
		pcc_ss_data->pending_pcc_write_cmd = true;
		cpc_desc->write_cmd_id = pcc_ss_data->pcc_write_cnt;
		cpc_desc->write_cmd_status = 0;
	}

	/*
	 * Skip writing MIN/MAX until Linux knows how to come up with
	 * useful values.
	 */
	cpc_write(cpu, desired_reg, perf_ctrls->desired_perf);

	if (CPC_IN_PCC(desired_reg))
		up_read(&pcc_ss_data->pcc_lock);	/* END Phase-I */
	/*
	 * This is Phase-II where we transfer the ownership of PCC to Platform
	 *
	 * Short Summary: Basically if we think of a group of cppc_set_perf
	 * requests that happened in short overlapping interval. The last CPU to
	 * come out of Phase-I will enter Phase-II and ring the doorbell.
	 *
	 * We have the following requirements for Phase-II:
	 *     1. We want to execute Phase-II only when there are no CPUs
	 * currently executing in Phase-I
	 *     2. Once we start Phase-II we want to avoid all other CPUs from
	 * entering Phase-I.
	 *     3. We want only one CPU among all those who went through Phase-I
	 * to run phase-II
	 *
	 * If write_trylock fails to get the lock and doesn't transfer the
	 * PCC ownership to the platform, then one of the following will be TRUE
	 *     1. There is at-least one CPU in Phase-I which will later execute
	 * write_trylock, so the CPUs in Phase-I will be responsible for
	 * executing the Phase-II.
	 *     2. Some other CPU has beaten this CPU to successfully execute the
	 * write_trylock and has already acquired the write_lock. We know for a
	 * fact it (other CPU acquiring the write_lock) couldn't have happened
	 * before this CPU's Phase-I as we held the read_lock.
	 *     3. Some other CPU executing pcc CMD_READ has stolen the
	 * down_write, in which case, send_pcc_cmd will check for pending
	 * CMD_WRITE commands by checking the pending_pcc_write_cmd.
	 * So this CPU can be certain that its request will be delivered
	 *    So in all cases, this CPU knows that its request will be delivered
	 * by another CPU and can return
	 *
	 * After getting the down_write we still need to check for
	 * pending_pcc_write_cmd to take care of the following scenario
	 *    The thread running this code could be scheduled out between
	 * Phase-I and Phase-II. Before it is scheduled back on, another CPU
	 * could have delivered the request to Platform by triggering the
	 * doorbell and transferred the ownership of PCC to platform. So this
	 * avoids triggering an unnecessary doorbell and more importantly before
	 * triggering the doorbell it makes sure that the PCC channel ownership
	 * is still with OSPM.
	 *   pending_pcc_write_cmd can also be cleared by a different CPU, if
	 * there was a pcc CMD_READ waiting on down_write and it steals the lock
	 * before the pcc CMD_WRITE is completed. pcc_send_cmd checks for this
	 * case during a CMD_READ and if there are pending writes it delivers
	 * the write command before servicing the read command
	 */
	if (CPC_IN_PCC(desired_reg)) {
		if (down_write_trylock(&pcc_ss_data->pcc_lock)) {/* BEGIN Phase-II */
			/* Update only if there are pending write commands */
			if (pcc_ss_data->pending_pcc_write_cmd)
				send_pcc_cmd(pcc_ss_id, CMD_WRITE);
			up_write(&pcc_ss_data->pcc_lock);	/* END Phase-II */
		} else
			/* Wait until pcc_write_cnt is updated by send_pcc_cmd */
			wait_event(pcc_ss_data->pcc_write_wait_q,
				   cpc_desc->write_cmd_id != pcc_ss_data->pcc_write_cnt);

		/* send_pcc_cmd updates the status in case of failure */
		ret = cpc_desc->write_cmd_status;
	}
	return ret;
}