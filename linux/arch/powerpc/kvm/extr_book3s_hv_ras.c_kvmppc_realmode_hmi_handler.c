#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  hmi_exceptions; } ;
struct TYPE_7__ {TYPE_1__* kvm_vcore; } ;
struct TYPE_9__ {TYPE_2__ kvm_hstate; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* hmi_exception_early ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {scalar_t__ tb_offset_applied; } ;

/* Variables and functions */
 int /*<<< orphan*/  __this_cpu_inc (int /*<<< orphan*/ ) ; 
 scalar_t__ hmi_handle_debugtrig (int /*<<< orphan*/ *) ; 
 TYPE_5__ irq_stat ; 
 int /*<<< orphan*/  kvmppc_subcore_exit_guest () ; 
 int /*<<< orphan*/  kvmppc_tb_resync_done () ; 
 int kvmppc_tb_resync_required () ; 
 TYPE_4__* local_paca ; 
 int /*<<< orphan*/  opal_resync_timebase () ; 
 TYPE_3__ ppc_md ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_subcore_guest_exit () ; 
 int /*<<< orphan*/  wait_for_tb_resync () ; 

long kvmppc_realmode_hmi_handler(void)
{
	bool resync_req;

	__this_cpu_inc(irq_stat.hmi_exceptions);

	if (hmi_handle_debugtrig(NULL) >= 0)
		return 1;

	/*
	 * By now primary thread has already completed guest->host
	 * partition switch but haven't signaled secondaries yet.
	 * All the secondary threads on this subcore is waiting
	 * for primary thread to signal them to go ahead.
	 *
	 * For threads from subcore which isn't in guest, they all will
	 * wait until all other subcores on this core exit the guest.
	 *
	 * Now set the resync required bit. If you are the first to
	 * set this bit then kvmppc_tb_resync_required() function will
	 * return true. For rest all other subcores
	 * kvmppc_tb_resync_required() will return false.
	 *
	 * If resync_req == true, then this thread is responsible to
	 * initiate TB resync after hmi handler has completed.
	 * All other threads on this core will wait until this thread
	 * clears the resync required bit flag.
	 */
	resync_req = kvmppc_tb_resync_required();

	/* Reset the subcore status to indicate it has exited guest */
	kvmppc_subcore_exit_guest();

	/*
	 * Wait for other subcores on this core to exit the guest.
	 * All the primary threads and threads from subcore that are
	 * not in guest will wait here until all subcores are out
	 * of guest context.
	 */
	wait_for_subcore_guest_exit();

	/*
	 * At this point we are sure that primary threads from each
	 * subcore on this core have completed guest->host partition
	 * switch. Now it is safe to call HMI handler.
	 */
	if (ppc_md.hmi_exception_early)
		ppc_md.hmi_exception_early(NULL);

	/*
	 * Check if this thread is responsible to resync TB.
	 * All other threads will wait until this thread completes the
	 * TB resync.
	 */
	if (resync_req) {
		opal_resync_timebase();
		/* Reset TB resync req bit */
		kvmppc_tb_resync_done();
	} else {
		wait_for_tb_resync();
	}

	/*
	 * Reset tb_offset_applied so the guest exit code won't try
	 * to subtract the previous timebase offset from the timebase.
	 */
	if (local_paca->kvm_hstate.kvm_vcore)
		local_paca->kvm_hstate.kvm_vcore->tb_offset_applied = 0;

	return 0;
}