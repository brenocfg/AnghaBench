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
typedef  int /*<<< orphan*/  u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {struct ecore_dev* p_dev; } ;
struct ecore_dev {int recov_in_prog; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,...) ; 
 struct ecore_hwfn* ECORE_LEADING_HWFN (struct ecore_dev*) ; 
 int /*<<< orphan*/  OSAL_SCHEDULE_RECOVERY_HANDLER (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_get_process_kill_counter (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int /*<<< orphan*/  ecore_int_igu_disable_int (struct ecore_hwfn*,struct ecore_ptt*) ; 

__attribute__((used)) static void ecore_mcp_handle_process_kill(struct ecore_hwfn *p_hwfn,
					  struct ecore_ptt *p_ptt)
{
	struct ecore_dev *p_dev = p_hwfn->p_dev;
	u32 proc_kill_cnt;

	/* Prevent possible attentions/interrupts during the recovery handling
	 * and till its load phase, during which they will be re-enabled.
	 */
	ecore_int_igu_disable_int(p_hwfn, p_ptt);

	DP_NOTICE(p_hwfn, false, "Received a process kill indication\n");

	/* The following operations should be done once, and thus in CMT mode
	 * are carried out by only the first HW function.
	 */
	if (p_hwfn != ECORE_LEADING_HWFN(p_dev))
		return;

	if (p_dev->recov_in_prog) {
		DP_NOTICE(p_hwfn, false,
			  "Ignoring the indication since a recovery process is already in progress\n");
		return;
	}

	p_dev->recov_in_prog = true;

	proc_kill_cnt = ecore_get_process_kill_counter(p_hwfn, p_ptt);
	DP_NOTICE(p_hwfn, false, "Process kill counter: %d\n", proc_kill_cnt);

	OSAL_SCHEDULE_RECOVERY_HANDLER(p_hwfn);
}