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
typedef  int u16 ;
struct trap_per_cpu {int cpu_list_pa; int cpu_mondo_block_pa; } ;

/* Variables and functions */
 unsigned long CPU_MONDO_COUNTER (int) ; 
 scalar_t__ HV_CPU_STATE_ERROR ; 
 unsigned long HV_ECPUERROR ; 
 unsigned long HV_ENOCPU ; 
 unsigned long HV_EOK ; 
 unsigned long HV_EWOULDBLOCK ; 
 int MONDO_RETRY_LIMIT ; 
 int MONDO_USEC_WAIT_MAX ; 
 int MONDO_USEC_WAIT_MIN ; 
 int* __va (int) ; 
 int /*<<< orphan*/  cpu_online (int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  pr_crit (char*,int,int,...) ; 
 int smp_processor_id () ; 
 unsigned long sun4v_cpu_mondo_send (int,int,int) ; 
 scalar_t__ sun4v_cpu_state (int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void hypervisor_xcall_deliver(struct trap_per_cpu *tb, int cnt)
{
	int this_cpu, tot_cpus, prev_sent, i, rem;
	int usec_wait, retries, tot_retries;
	u16 first_cpu = 0xffff;
	unsigned long xc_rcvd = 0;
	unsigned long status;
	int ecpuerror_id = 0;
	int enocpu_id = 0;
	u16 *cpu_list;
	u16 cpu;

	this_cpu = smp_processor_id();
	cpu_list = __va(tb->cpu_list_pa);
	usec_wait = cnt * MONDO_USEC_WAIT_MIN;
	if (usec_wait > MONDO_USEC_WAIT_MAX)
		usec_wait = MONDO_USEC_WAIT_MAX;
	retries = tot_retries = 0;
	tot_cpus = cnt;
	prev_sent = 0;

	do {
		int n_sent, mondo_delivered, target_cpu_busy;

		status = sun4v_cpu_mondo_send(cnt,
					      tb->cpu_list_pa,
					      tb->cpu_mondo_block_pa);

		/* HV_EOK means all cpus received the xcall, we're done.  */
		if (likely(status == HV_EOK))
			goto xcall_done;

		/* If not these non-fatal errors, panic */
		if (unlikely((status != HV_EWOULDBLOCK) &&
			(status != HV_ECPUERROR) &&
			(status != HV_ENOCPU)))
			goto fatal_errors;

		/* First, see if we made any forward progress.
		 *
		 * Go through the cpu_list, count the target cpus that have
		 * received our mondo (n_sent), and those that did not (rem).
		 * Re-pack cpu_list with the cpus remain to be retried in the
		 * front - this simplifies tracking the truly stalled cpus.
		 *
		 * The hypervisor indicates successful sends by setting
		 * cpu list entries to the value 0xffff.
		 *
		 * EWOULDBLOCK means some target cpus did not receive the
		 * mondo and retry usually helps.
		 *
		 * ECPUERROR means at least one target cpu is in error state,
		 * it's usually safe to skip the faulty cpu and retry.
		 *
		 * ENOCPU means one of the target cpu doesn't belong to the
		 * domain, perhaps offlined which is unexpected, but not
		 * fatal and it's okay to skip the offlined cpu.
		 */
		rem = 0;
		n_sent = 0;
		for (i = 0; i < cnt; i++) {
			cpu = cpu_list[i];
			if (likely(cpu == 0xffff)) {
				n_sent++;
			} else if ((status == HV_ECPUERROR) &&
				(sun4v_cpu_state(cpu) == HV_CPU_STATE_ERROR)) {
				ecpuerror_id = cpu + 1;
			} else if (status == HV_ENOCPU && !cpu_online(cpu)) {
				enocpu_id = cpu + 1;
			} else {
				cpu_list[rem++] = cpu;
			}
		}

		/* No cpu remained, we're done. */
		if (rem == 0)
			break;

		/* Otherwise, update the cpu count for retry. */
		cnt = rem;

		/* Record the overall number of mondos received by the
		 * first of the remaining cpus.
		 */
		if (first_cpu != cpu_list[0]) {
			first_cpu = cpu_list[0];
			xc_rcvd = CPU_MONDO_COUNTER(first_cpu);
		}

		/* Was any mondo delivered successfully? */
		mondo_delivered = (n_sent > prev_sent);
		prev_sent = n_sent;

		/* or, was any target cpu busy processing other mondos? */
		target_cpu_busy = (xc_rcvd < CPU_MONDO_COUNTER(first_cpu));
		xc_rcvd = CPU_MONDO_COUNTER(first_cpu);

		/* Retry count is for no progress. If we're making progress,
		 * reset the retry count.
		 */
		if (likely(mondo_delivered || target_cpu_busy)) {
			tot_retries += retries;
			retries = 0;
		} else if (unlikely(retries > MONDO_RETRY_LIMIT)) {
			goto fatal_mondo_timeout;
		}

		/* Delay a little bit to let other cpus catch up on
		 * their cpu mondo queue work.
		 */
		if (!mondo_delivered)
			udelay(usec_wait);

		retries++;
	} while (1);

xcall_done:
	if (unlikely(ecpuerror_id > 0)) {
		pr_crit("CPU[%d]: SUN4V mondo cpu error, target cpu(%d) was in error state\n",
		       this_cpu, ecpuerror_id - 1);
	} else if (unlikely(enocpu_id > 0)) {
		pr_crit("CPU[%d]: SUN4V mondo cpu error, target cpu(%d) does not belong to the domain\n",
		       this_cpu, enocpu_id - 1);
	}
	return;

fatal_errors:
	/* fatal errors include bad alignment, etc */
	pr_crit("CPU[%d]: Args were cnt(%d) cpulist_pa(%lx) mondo_block_pa(%lx)\n",
	       this_cpu, tot_cpus, tb->cpu_list_pa, tb->cpu_mondo_block_pa);
	panic("Unexpected SUN4V mondo error %lu\n", status);

fatal_mondo_timeout:
	/* some cpus being non-responsive to the cpu mondo */
	pr_crit("CPU[%d]: SUN4V mondo timeout, cpu(%d) made no forward progress after %d retries. Total target cpus(%d).\n",
	       this_cpu, first_cpu, (tot_retries + retries), tot_cpus);
	panic("SUN4V mondo timeout panic\n");
}