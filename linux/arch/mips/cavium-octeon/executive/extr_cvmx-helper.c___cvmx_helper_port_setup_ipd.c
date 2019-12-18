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
struct TYPE_4__ {scalar_t__ grp; void* non_tag_type; void* ip4_tag_type; void* ip6_tag_type; void* tcp4_tag_type; void* tcp6_tag_type; int /*<<< orphan*/  inc_prt_flag; int /*<<< orphan*/  ip4_pctl_flag; int /*<<< orphan*/  ip4_dprt_flag; int /*<<< orphan*/  ip4_sprt_flag; int /*<<< orphan*/  ip4_dst_flag; int /*<<< orphan*/  ip4_src_flag; int /*<<< orphan*/  ip6_nxth_flag; int /*<<< orphan*/  ip6_dprt_flag; int /*<<< orphan*/  ip6_sprt_flag; int /*<<< orphan*/  ip6_dst_flag; int /*<<< orphan*/  ip6_src_flag; } ;
union cvmx_pip_prt_tagx {TYPE_2__ s; void* u64; } ;
struct TYPE_3__ {int qos; int /*<<< orphan*/  mode; } ;
union cvmx_pip_prt_cfgx {TYPE_1__ s; void* u64; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_HELPER_INPUT_PORT_SKIP_MODE ; 
 int /*<<< orphan*/  CVMX_HELPER_INPUT_TAG_INPUT_PORT ; 
 int /*<<< orphan*/  CVMX_HELPER_INPUT_TAG_IPV4_DST_IP ; 
 int /*<<< orphan*/  CVMX_HELPER_INPUT_TAG_IPV4_DST_PORT ; 
 int /*<<< orphan*/  CVMX_HELPER_INPUT_TAG_IPV4_PROTOCOL ; 
 int /*<<< orphan*/  CVMX_HELPER_INPUT_TAG_IPV4_SRC_IP ; 
 int /*<<< orphan*/  CVMX_HELPER_INPUT_TAG_IPV4_SRC_PORT ; 
 int /*<<< orphan*/  CVMX_HELPER_INPUT_TAG_IPV6_DST_IP ; 
 int /*<<< orphan*/  CVMX_HELPER_INPUT_TAG_IPV6_DST_PORT ; 
 int /*<<< orphan*/  CVMX_HELPER_INPUT_TAG_IPV6_NEXT_HEADER ; 
 int /*<<< orphan*/  CVMX_HELPER_INPUT_TAG_IPV6_SRC_IP ; 
 int /*<<< orphan*/  CVMX_HELPER_INPUT_TAG_IPV6_SRC_PORT ; 
 void* CVMX_HELPER_INPUT_TAG_TYPE ; 
 int /*<<< orphan*/  CVMX_PIP_PRT_CFGX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_PRT_TAGX (int) ; 
 int /*<<< orphan*/  cvmx_pip_config_port (int,union cvmx_pip_prt_cfgx,union cvmx_pip_prt_tagx) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __cvmx_helper_port_setup_ipd(int ipd_port)
{
	union cvmx_pip_prt_cfgx port_config;
	union cvmx_pip_prt_tagx tag_config;

	port_config.u64 = cvmx_read_csr(CVMX_PIP_PRT_CFGX(ipd_port));
	tag_config.u64 = cvmx_read_csr(CVMX_PIP_PRT_TAGX(ipd_port));

	/* Have each port go to a different POW queue */
	port_config.s.qos = ipd_port & 0x7;

	/* Process the headers and place the IP header in the work queue */
	port_config.s.mode = CVMX_HELPER_INPUT_PORT_SKIP_MODE;

	tag_config.s.ip6_src_flag = CVMX_HELPER_INPUT_TAG_IPV6_SRC_IP;
	tag_config.s.ip6_dst_flag = CVMX_HELPER_INPUT_TAG_IPV6_DST_IP;
	tag_config.s.ip6_sprt_flag = CVMX_HELPER_INPUT_TAG_IPV6_SRC_PORT;
	tag_config.s.ip6_dprt_flag = CVMX_HELPER_INPUT_TAG_IPV6_DST_PORT;
	tag_config.s.ip6_nxth_flag = CVMX_HELPER_INPUT_TAG_IPV6_NEXT_HEADER;
	tag_config.s.ip4_src_flag = CVMX_HELPER_INPUT_TAG_IPV4_SRC_IP;
	tag_config.s.ip4_dst_flag = CVMX_HELPER_INPUT_TAG_IPV4_DST_IP;
	tag_config.s.ip4_sprt_flag = CVMX_HELPER_INPUT_TAG_IPV4_SRC_PORT;
	tag_config.s.ip4_dprt_flag = CVMX_HELPER_INPUT_TAG_IPV4_DST_PORT;
	tag_config.s.ip4_pctl_flag = CVMX_HELPER_INPUT_TAG_IPV4_PROTOCOL;
	tag_config.s.inc_prt_flag = CVMX_HELPER_INPUT_TAG_INPUT_PORT;
	tag_config.s.tcp6_tag_type = CVMX_HELPER_INPUT_TAG_TYPE;
	tag_config.s.tcp4_tag_type = CVMX_HELPER_INPUT_TAG_TYPE;
	tag_config.s.ip6_tag_type = CVMX_HELPER_INPUT_TAG_TYPE;
	tag_config.s.ip4_tag_type = CVMX_HELPER_INPUT_TAG_TYPE;
	tag_config.s.non_tag_type = CVMX_HELPER_INPUT_TAG_TYPE;
	/* Put all packets in group 0. Other groups can be used by the app */
	tag_config.s.grp = 0;

	cvmx_pip_config_port(ipd_port, port_config, tag_config);

	return 0;
}