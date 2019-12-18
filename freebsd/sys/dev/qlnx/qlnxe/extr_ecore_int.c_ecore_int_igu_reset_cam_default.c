#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ecore_sb_cnt_info {scalar_t__ iov_orig; scalar_t__ orig; scalar_t__ free_cnt_iov; scalar_t__ iov_cnt; scalar_t__ free_cnt; scalar_t__ cnt; } ;
struct ecore_ptt {int dummy; } ;
struct TYPE_4__ {TYPE_1__* p_igu_info; } ;
struct ecore_hwfn {TYPE_2__ hw_info; } ;
struct TYPE_3__ {struct ecore_sb_cnt_info usage; } ;

/* Variables and functions */
 int ecore_int_igu_reset_cam (struct ecore_hwfn*,struct ecore_ptt*) ; 

int ecore_int_igu_reset_cam_default(struct ecore_hwfn *p_hwfn,
				    struct ecore_ptt *p_ptt)
{
	struct ecore_sb_cnt_info *p_cnt = &p_hwfn->hw_info.p_igu_info->usage;

	/* Return all the usage indications to default prior to the reset;
	 * The reset expects the !orig to reflect the initial status of the
	 * SBs, and would re-calculate the originals based on those.
	 */
	p_cnt->cnt = p_cnt->orig;
	p_cnt->free_cnt = p_cnt->orig;
	p_cnt->iov_cnt = p_cnt->iov_orig;
	p_cnt->free_cnt_iov = p_cnt->iov_orig;
	p_cnt->orig = 0;
	p_cnt->iov_orig = 0;

	/* TODO - we probably need to re-configure the CAU as well... */
	return ecore_int_igu_reset_cam(p_hwfn, p_ptt);
}