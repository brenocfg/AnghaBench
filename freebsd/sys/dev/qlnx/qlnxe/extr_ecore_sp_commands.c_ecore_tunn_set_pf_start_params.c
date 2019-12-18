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
struct pf_start_tunnel_config {int /*<<< orphan*/  tunnel_clss_ipgre; int /*<<< orphan*/  tunnel_clss_l2gre; int /*<<< orphan*/  tunnel_clss_ipgeneve; int /*<<< orphan*/  geneve_udp_port; int /*<<< orphan*/  set_geneve_udp_port_flg; int /*<<< orphan*/  tunnel_clss_l2geneve; int /*<<< orphan*/  vxlan_udp_port; int /*<<< orphan*/  set_vxlan_udp_port_flg; int /*<<< orphan*/  tunnel_clss_vxlan; } ;
struct ecore_tunnel_info {int /*<<< orphan*/  ip_gre; int /*<<< orphan*/  l2_gre; int /*<<< orphan*/  ip_geneve; int /*<<< orphan*/  geneve_port; int /*<<< orphan*/  l2_geneve; int /*<<< orphan*/  vxlan_port; int /*<<< orphan*/  vxlan; } ;
struct ecore_hwfn {TYPE_1__* p_dev; } ;
struct TYPE_2__ {struct ecore_tunnel_info tunnel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 scalar_t__ ECORE_IS_BB_A0 (TYPE_1__*) ; 
 int /*<<< orphan*/  __ecore_set_ramrod_tunnel_param (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecore_set_pf_update_tunn_mode (struct ecore_tunnel_info*,struct ecore_tunnel_info*,int) ; 
 int /*<<< orphan*/  ecore_set_ramrod_tunnel_param (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecore_set_tunn_cls_info (struct ecore_tunnel_info*,struct ecore_tunnel_info*) ; 
 int /*<<< orphan*/  ecore_set_tunn_ports (struct ecore_tunnel_info*,struct ecore_tunnel_info*) ; 

__attribute__((used)) static void
ecore_tunn_set_pf_start_params(struct ecore_hwfn		*p_hwfn,
			       struct ecore_tunnel_info		*p_src,
			       struct pf_start_tunnel_config	*p_tunn_cfg)
{
	struct ecore_tunnel_info *p_tun = &p_hwfn->p_dev->tunnel;

	if (ECORE_IS_BB_A0(p_hwfn->p_dev)) {
		DP_NOTICE(p_hwfn, true,
			  "A0 chip: tunnel pf start config is not supported\n");
		return;
	}

	if (!p_src)
		return;

	ecore_set_pf_update_tunn_mode(p_tun, p_src, true);
	ecore_set_tunn_cls_info(p_tun, p_src);
	ecore_set_tunn_ports(p_tun, p_src);

	ecore_set_ramrod_tunnel_param(&p_tunn_cfg->tunnel_clss_vxlan,
				      &p_tun->vxlan,
				      &p_tunn_cfg->set_vxlan_udp_port_flg,
				      &p_tunn_cfg->vxlan_udp_port,
				      &p_tun->vxlan_port);

	ecore_set_ramrod_tunnel_param(&p_tunn_cfg->tunnel_clss_l2geneve,
				      &p_tun->l2_geneve,
				      &p_tunn_cfg->set_geneve_udp_port_flg,
				      &p_tunn_cfg->geneve_udp_port,
				      &p_tun->geneve_port);

	__ecore_set_ramrod_tunnel_param(&p_tunn_cfg->tunnel_clss_ipgeneve,
					&p_tun->ip_geneve);

	__ecore_set_ramrod_tunnel_param(&p_tunn_cfg->tunnel_clss_l2gre,
					&p_tun->l2_gre);

	__ecore_set_ramrod_tunnel_param(&p_tunn_cfg->tunnel_clss_ipgre,
					&p_tun->ip_gre);
}