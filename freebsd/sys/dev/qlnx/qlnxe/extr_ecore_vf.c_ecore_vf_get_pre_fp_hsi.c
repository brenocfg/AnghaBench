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
struct ecore_hwfn {TYPE_1__* vf_iov_info; } ;
struct TYPE_2__ {int b_pre_fp_hsi; } ;

/* Variables and functions */

bool ecore_vf_get_pre_fp_hsi(struct ecore_hwfn *p_hwfn)
{
	return p_hwfn->vf_iov_info->b_pre_fp_hsi;
}