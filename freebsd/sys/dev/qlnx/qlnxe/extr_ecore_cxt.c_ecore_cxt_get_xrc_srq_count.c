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
typedef  int /*<<< orphan*/  u32 ;
struct ecore_hwfn {TYPE_1__* p_cxt_mngr; } ;
struct TYPE_2__ {int /*<<< orphan*/  xrc_srq_count; } ;

/* Variables and functions */

u32 ecore_cxt_get_xrc_srq_count(struct ecore_hwfn *p_hwfn)
{
	return p_hwfn->p_cxt_mngr->xrc_srq_count;
}