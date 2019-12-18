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
struct ecore_hwfn {struct ecore_cxt_mngr* p_cxt_mngr; } ;
struct ecore_cxt_mngr {scalar_t__ xrc_srq_count; int /*<<< orphan*/  srq_count; } ;

/* Variables and functions */
 scalar_t__ ecore_cxt_srqs_per_page (struct ecore_hwfn*) ; 

u32 ecore_cxt_get_total_srq_count(struct ecore_hwfn *p_hwfn)
{
	struct ecore_cxt_mngr *p_mgr = p_hwfn->p_cxt_mngr;
	u32 total_srqs;

	total_srqs = p_mgr->srq_count;

	/* XRC SRQs use the first and only the first SRQ ILT page. So if XRC
	 * SRQs are requested we need to allocate an extra SRQ ILT page for
	 * them. For that We increase the number of regular SRQs to cause the
	 * allocation of that extra page.
	 */
	if (p_mgr->xrc_srq_count)
		total_srqs += ecore_cxt_srqs_per_page(p_hwfn);

	return total_srqs;
}