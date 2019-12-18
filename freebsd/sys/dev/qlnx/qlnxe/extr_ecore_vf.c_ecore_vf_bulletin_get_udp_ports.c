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
typedef  int /*<<< orphan*/  u16 ;
struct ecore_hwfn {TYPE_1__* vf_iov_info; } ;
struct ecore_bulletin_content {int /*<<< orphan*/  geneve_udp_port; int /*<<< orphan*/  vxlan_udp_port; } ;
struct TYPE_2__ {struct ecore_bulletin_content bulletin_shadow; } ;

/* Variables and functions */

void ecore_vf_bulletin_get_udp_ports(struct ecore_hwfn *p_hwfn,
				     u16 *p_vxlan_port,
				     u16 *p_geneve_port)
{
	struct ecore_bulletin_content *p_bulletin;

	p_bulletin = &p_hwfn->vf_iov_info->bulletin_shadow;

	*p_vxlan_port = p_bulletin->vxlan_udp_port;
	*p_geneve_port = p_bulletin->geneve_udp_port;
}