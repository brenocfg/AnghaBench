#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {TYPE_1__* mcp_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  mfw_mb_length; int /*<<< orphan*/  mfw_mb_cur; int /*<<< orphan*/  mfw_mb_shadow; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_MEMCPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_mcp_read_mb (struct ecore_hwfn*,struct ecore_ptt*) ; 

__attribute__((used)) static void ecore_reset_mb_shadow(struct ecore_hwfn *p_hwfn,
			struct ecore_ptt *p_main_ptt)
{
	/* Read shadow of current MFW mailbox */
	ecore_mcp_read_mb(p_hwfn, p_main_ptt);
	OSAL_MEMCPY(p_hwfn->mcp_info->mfw_mb_shadow,
		    p_hwfn->mcp_info->mfw_mb_cur,
		    p_hwfn->mcp_info->mfw_mb_length);
}