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
typedef  int /*<<< orphan*/  u8 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
struct ecore_dev {int /*<<< orphan*/  recov_in_prog; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ECORE_HW_STOP_RETRY_LIMIT ; 
 int /*<<< orphan*/  OSAL_MSLEEP (int) ; 
 int /*<<< orphan*/  TM_REG_PF_ENABLE_CONN ; 
 int /*<<< orphan*/  TM_REG_PF_ENABLE_TASK ; 
 int /*<<< orphan*/  TM_REG_PF_SCAN_ACTIVE_CONN ; 
 int /*<<< orphan*/  TM_REG_PF_SCAN_ACTIVE_TASK ; 
 scalar_t__ ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ecore_hw_timers_stop(struct ecore_dev *p_dev,
				 struct ecore_hwfn *p_hwfn,
				 struct ecore_ptt *p_ptt)
{
	int i;

	/* close timers */
	ecore_wr(p_hwfn, p_ptt, TM_REG_PF_ENABLE_CONN, 0x0);
	ecore_wr(p_hwfn, p_ptt, TM_REG_PF_ENABLE_TASK, 0x0);
	for (i = 0;
	     i < ECORE_HW_STOP_RETRY_LIMIT && !p_dev->recov_in_prog;
	     i++) {
		if ((!ecore_rd(p_hwfn, p_ptt,
			       TM_REG_PF_SCAN_ACTIVE_CONN)) &&
		    (!ecore_rd(p_hwfn, p_ptt,
			       TM_REG_PF_SCAN_ACTIVE_TASK)))
			break;

		/* Dependent on number of connection/tasks, possibly
		 * 1ms sleep is required between polls
		 */
		OSAL_MSLEEP(1);
	}

	if (i < ECORE_HW_STOP_RETRY_LIMIT)
		return;

	DP_NOTICE(p_hwfn, false,
		  "Timers linear scans are not over [Connection %02x Tasks %02x]\n",
		  (u8)ecore_rd(p_hwfn, p_ptt, TM_REG_PF_SCAN_ACTIVE_CONN),
		  (u8)ecore_rd(p_hwfn, p_ptt, TM_REG_PF_SCAN_ACTIVE_TASK));
}