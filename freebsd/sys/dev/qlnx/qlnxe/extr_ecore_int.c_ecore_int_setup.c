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
struct ecore_hwfn {TYPE_1__* p_sp_sb; int /*<<< orphan*/  p_sb_attn; } ;
struct TYPE_2__ {int /*<<< orphan*/  sb_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ecore_int_sb_attn_setup (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int /*<<< orphan*/  ecore_int_sb_setup (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecore_int_sp_dpc_setup (struct ecore_hwfn*) ; 

void ecore_int_setup(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt)
{
	if (!p_hwfn || !p_hwfn->p_sp_sb || !p_hwfn->p_sb_attn)
		return;

	ecore_int_sb_setup(p_hwfn, p_ptt, &p_hwfn->p_sp_sb->sb_info);
	ecore_int_sb_attn_setup(p_hwfn, p_ptt);
	ecore_int_sp_dpc_setup(p_hwfn);
}