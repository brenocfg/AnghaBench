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
typedef  int /*<<< orphan*/  u32 ;
struct ecore_sb_info {int /*<<< orphan*/  igu_sb_id; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum ecore_coalescing_fsm { ____Placeholder_ecore_coalescing_fsm } ecore_coalescing_fsm ;

/* Variables and functions */
 int /*<<< orphan*/  _ecore_int_cau_conf_pi (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void ecore_int_cau_conf_pi(struct ecore_hwfn *p_hwfn,
			   struct ecore_ptt *p_ptt,
			   struct ecore_sb_info *p_sb, u32 pi_index,
			   enum ecore_coalescing_fsm coalescing_fsm,
			   u8 timeset)
{
	_ecore_int_cau_conf_pi(p_hwfn, p_ptt, p_sb->igu_sb_id,
			       pi_index, coalescing_fsm, timeset);
}