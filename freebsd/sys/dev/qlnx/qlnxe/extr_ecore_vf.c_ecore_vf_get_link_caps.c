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
struct ecore_mcp_link_capabilities {int dummy; } ;
struct ecore_hwfn {TYPE_1__* vf_iov_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  bulletin_shadow; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ecore_vf_get_link_caps (struct ecore_mcp_link_capabilities*,int /*<<< orphan*/ *) ; 

void ecore_vf_get_link_caps(struct ecore_hwfn *p_hwfn,
			    struct ecore_mcp_link_capabilities *p_link_caps)
{
	__ecore_vf_get_link_caps(p_link_caps,
				 &(p_hwfn->vf_iov_info->bulletin_shadow));
}