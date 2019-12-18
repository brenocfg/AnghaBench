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
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int abs_pf_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  PGLUE_B_REG_WAS_ERROR_PF_31_0_CLR ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ecore_pglueb_clear_err(struct ecore_hwfn *p_hwfn,
				   struct ecore_ptt *p_ptt)
{
	ecore_wr(p_hwfn, p_ptt, PGLUE_B_REG_WAS_ERROR_PF_31_0_CLR,
		 1 << p_hwfn->abs_pf_id);
}