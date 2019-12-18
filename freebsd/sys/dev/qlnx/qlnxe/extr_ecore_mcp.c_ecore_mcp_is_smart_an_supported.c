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
struct ecore_hwfn {TYPE_1__* mcp_info; } ;
struct TYPE_2__ {int capabilities; } ;

/* Variables and functions */
 int FW_MB_PARAM_FEATURE_SUPPORT_SMARTLINQ ; 

bool ecore_mcp_is_smart_an_supported(struct ecore_hwfn *p_hwfn)
{
	return !!(p_hwfn->mcp_info->capabilities &
		  FW_MB_PARAM_FEATURE_SUPPORT_SMARTLINQ);
}