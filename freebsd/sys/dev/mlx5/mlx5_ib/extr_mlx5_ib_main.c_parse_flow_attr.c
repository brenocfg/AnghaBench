#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_26__ {int /*<<< orphan*/  dst_port; int /*<<< orphan*/  src_port; } ;
struct TYPE_21__ {int /*<<< orphan*/  dst_port; int /*<<< orphan*/  src_port; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  next_hdr; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  dst_ip; int /*<<< orphan*/  src_ip; int /*<<< orphan*/  proto; int /*<<< orphan*/  tos; int /*<<< orphan*/  ether_type; int /*<<< orphan*/  vlan_tag; int /*<<< orphan*/  src_mac; int /*<<< orphan*/  dst_mac; } ;
struct TYPE_27__ {TYPE_5__ val; TYPE_15__ mask; } ;
struct TYPE_24__ {int /*<<< orphan*/  flow_label; int /*<<< orphan*/  next_hdr; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  dst_ip; int /*<<< orphan*/  src_ip; } ;
struct TYPE_25__ {TYPE_3__ val; TYPE_15__ mask; } ;
struct TYPE_17__ {int /*<<< orphan*/  proto; int /*<<< orphan*/  tos; int /*<<< orphan*/  dst_ip; int /*<<< orphan*/  src_ip; } ;
struct TYPE_18__ {TYPE_11__ val; TYPE_15__ mask; } ;
struct TYPE_28__ {int /*<<< orphan*/  ether_type; int /*<<< orphan*/  vlan_tag; int /*<<< orphan*/  src_mac; int /*<<< orphan*/  dst_mac; } ;
struct TYPE_29__ {TYPE_7__ val; TYPE_15__ mask; } ;
union ib_flow_spec {int type; TYPE_6__ tcp_udp; TYPE_4__ ipv6; TYPE_12__ ipv4; TYPE_8__ eth; } ;
typedef  void u32 ;
struct TYPE_30__ {int /*<<< orphan*/  ipv4; } ;
struct TYPE_23__ {int /*<<< orphan*/  ipv6; } ;
struct TYPE_22__ {int /*<<< orphan*/  ipv6; } ;
struct TYPE_16__ {int /*<<< orphan*/  ipv4; } ;
struct TYPE_20__ {TYPE_2__ ipv6_layout; TYPE_10__ ipv4_layout; } ;
struct TYPE_19__ {TYPE_1__ ipv6_layout; TYPE_9__ ipv4_layout; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int ETH_P_IP ; 
 int /*<<< orphan*/  FIELDS_NOT_SUPPORTED (TYPE_15__,int /*<<< orphan*/ ) ; 
#define  IB_FLOW_SPEC_ETH 132 
#define  IB_FLOW_SPEC_IPV4 131 
#define  IB_FLOW_SPEC_IPV6 130 
#define  IB_FLOW_SPEC_TCP 129 
#define  IB_FLOW_SPEC_UDP 128 
 int IPPROTO_IPV6 ; 
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 int /*<<< orphan*/  LAST_ETH_FIELD ; 
 int /*<<< orphan*/  LAST_IPV4_FIELD ; 
 int /*<<< orphan*/  LAST_IPV6_FIELD ; 
 int /*<<< orphan*/  LAST_TCP_UDP_FIELD ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cvlan_tag ; 
 int /*<<< orphan*/  dmac_47_16 ; 
 TYPE_14__ dst_ipv4_dst_ipv6 ; 
 int /*<<< orphan*/  ether_addr_copy (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethertype ; 
 int /*<<< orphan*/  first_cfi ; 
 int /*<<< orphan*/  first_prio ; 
 int /*<<< orphan*/  first_vid ; 
 int /*<<< orphan*/  fte_match_param ; 
 int /*<<< orphan*/  fte_match_set_lyr_2_4 ; 
 int /*<<< orphan*/  fte_match_set_misc ; 
 int /*<<< orphan*/  ip_protocol ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  misc_parameters ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outer_headers ; 
 int /*<<< orphan*/  outer_ipv6_flow_label ; 
 int /*<<< orphan*/  set_proto (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tos (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smac_47_16 ; 
 TYPE_13__ src_ipv4_src_ipv6 ; 
 int /*<<< orphan*/  tcp_dport ; 
 int /*<<< orphan*/  tcp_sport ; 
 int /*<<< orphan*/  udp_dport ; 
 int /*<<< orphan*/  udp_sport ; 

__attribute__((used)) static int parse_flow_attr(u32 *match_c, u32 *match_v,
			   const union ib_flow_spec *ib_spec)
{
	void *outer_headers_c = MLX5_ADDR_OF(fte_match_param, match_c,
					     outer_headers);
	void *outer_headers_v = MLX5_ADDR_OF(fte_match_param, match_v,
					     outer_headers);
	void *misc_params_c = MLX5_ADDR_OF(fte_match_param, match_c,
					   misc_parameters);
	void *misc_params_v = MLX5_ADDR_OF(fte_match_param, match_v,
					   misc_parameters);

	switch (ib_spec->type) {
	case IB_FLOW_SPEC_ETH:
		if (FIELDS_NOT_SUPPORTED(ib_spec->eth.mask, LAST_ETH_FIELD))
			return -ENOTSUPP;

		ether_addr_copy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, outer_headers_c,
					     dmac_47_16),
				ib_spec->eth.mask.dst_mac);
		ether_addr_copy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, outer_headers_v,
					     dmac_47_16),
				ib_spec->eth.val.dst_mac);

		ether_addr_copy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, outer_headers_c,
					     smac_47_16),
				ib_spec->eth.mask.src_mac);
		ether_addr_copy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, outer_headers_v,
					     smac_47_16),
				ib_spec->eth.val.src_mac);

		if (ib_spec->eth.mask.vlan_tag) {
			MLX5_SET(fte_match_set_lyr_2_4, outer_headers_c,
				 cvlan_tag, 1);
			MLX5_SET(fte_match_set_lyr_2_4, outer_headers_v,
				 cvlan_tag, 1);

			MLX5_SET(fte_match_set_lyr_2_4, outer_headers_c,
				 first_vid, ntohs(ib_spec->eth.mask.vlan_tag));
			MLX5_SET(fte_match_set_lyr_2_4, outer_headers_v,
				 first_vid, ntohs(ib_spec->eth.val.vlan_tag));

			MLX5_SET(fte_match_set_lyr_2_4, outer_headers_c,
				 first_cfi,
				 ntohs(ib_spec->eth.mask.vlan_tag) >> 12);
			MLX5_SET(fte_match_set_lyr_2_4, outer_headers_v,
				 first_cfi,
				 ntohs(ib_spec->eth.val.vlan_tag) >> 12);

			MLX5_SET(fte_match_set_lyr_2_4, outer_headers_c,
				 first_prio,
				 ntohs(ib_spec->eth.mask.vlan_tag) >> 13);
			MLX5_SET(fte_match_set_lyr_2_4, outer_headers_v,
				 first_prio,
				 ntohs(ib_spec->eth.val.vlan_tag) >> 13);
		}
		MLX5_SET(fte_match_set_lyr_2_4, outer_headers_c,
			 ethertype, ntohs(ib_spec->eth.mask.ether_type));
		MLX5_SET(fte_match_set_lyr_2_4, outer_headers_v,
			 ethertype, ntohs(ib_spec->eth.val.ether_type));
		break;
	case IB_FLOW_SPEC_IPV4:
		if (FIELDS_NOT_SUPPORTED(ib_spec->ipv4.mask, LAST_IPV4_FIELD))
			return -ENOTSUPP;

		MLX5_SET(fte_match_set_lyr_2_4, outer_headers_c,
			 ethertype, 0xffff);
		MLX5_SET(fte_match_set_lyr_2_4, outer_headers_v,
			 ethertype, ETH_P_IP);

		memcpy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, outer_headers_c,
				    src_ipv4_src_ipv6.ipv4_layout.ipv4),
		       &ib_spec->ipv4.mask.src_ip,
		       sizeof(ib_spec->ipv4.mask.src_ip));
		memcpy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, outer_headers_v,
				    src_ipv4_src_ipv6.ipv4_layout.ipv4),
		       &ib_spec->ipv4.val.src_ip,
		       sizeof(ib_spec->ipv4.val.src_ip));
		memcpy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, outer_headers_c,
				    dst_ipv4_dst_ipv6.ipv4_layout.ipv4),
		       &ib_spec->ipv4.mask.dst_ip,
		       sizeof(ib_spec->ipv4.mask.dst_ip));
		memcpy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, outer_headers_v,
				    dst_ipv4_dst_ipv6.ipv4_layout.ipv4),
		       &ib_spec->ipv4.val.dst_ip,
		       sizeof(ib_spec->ipv4.val.dst_ip));

		set_tos(outer_headers_c, outer_headers_v,
			ib_spec->ipv4.mask.tos, ib_spec->ipv4.val.tos);

		set_proto(outer_headers_c, outer_headers_v,
			  ib_spec->ipv4.mask.proto, ib_spec->ipv4.val.proto);
		break;
	case IB_FLOW_SPEC_IPV6:
		if (FIELDS_NOT_SUPPORTED(ib_spec->ipv6.mask, LAST_IPV6_FIELD))
			return -ENOTSUPP;

		MLX5_SET(fte_match_set_lyr_2_4, outer_headers_c,
			 ethertype, 0xffff);
		MLX5_SET(fte_match_set_lyr_2_4, outer_headers_v,
			 ethertype, IPPROTO_IPV6);

		memcpy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, outer_headers_c,
				    src_ipv4_src_ipv6.ipv6_layout.ipv6),
		       &ib_spec->ipv6.mask.src_ip,
		       sizeof(ib_spec->ipv6.mask.src_ip));
		memcpy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, outer_headers_v,
				    src_ipv4_src_ipv6.ipv6_layout.ipv6),
		       &ib_spec->ipv6.val.src_ip,
		       sizeof(ib_spec->ipv6.val.src_ip));
		memcpy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, outer_headers_c,
				    dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
		       &ib_spec->ipv6.mask.dst_ip,
		       sizeof(ib_spec->ipv6.mask.dst_ip));
		memcpy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, outer_headers_v,
				    dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
		       &ib_spec->ipv6.val.dst_ip,
		       sizeof(ib_spec->ipv6.val.dst_ip));

		set_tos(outer_headers_c, outer_headers_v,
			ib_spec->ipv6.mask.traffic_class,
			ib_spec->ipv6.val.traffic_class);

		set_proto(outer_headers_c, outer_headers_v,
			  ib_spec->ipv6.mask.next_hdr,
			  ib_spec->ipv6.val.next_hdr);

		MLX5_SET(fte_match_set_misc, misc_params_c,
			 outer_ipv6_flow_label,
			 ntohl(ib_spec->ipv6.mask.flow_label));
		MLX5_SET(fte_match_set_misc, misc_params_v,
			 outer_ipv6_flow_label,
			 ntohl(ib_spec->ipv6.val.flow_label));
		break;
	case IB_FLOW_SPEC_TCP:
		if (FIELDS_NOT_SUPPORTED(ib_spec->tcp_udp.mask,
					 LAST_TCP_UDP_FIELD))
			return -ENOTSUPP;

		MLX5_SET(fte_match_set_lyr_2_4, outer_headers_c, ip_protocol,
			 0xff);
		MLX5_SET(fte_match_set_lyr_2_4, outer_headers_v, ip_protocol,
			 IPPROTO_TCP);

		MLX5_SET(fte_match_set_lyr_2_4, outer_headers_c, tcp_sport,
			 ntohs(ib_spec->tcp_udp.mask.src_port));
		MLX5_SET(fte_match_set_lyr_2_4, outer_headers_v, tcp_sport,
			 ntohs(ib_spec->tcp_udp.val.src_port));

		MLX5_SET(fte_match_set_lyr_2_4, outer_headers_c, tcp_dport,
			 ntohs(ib_spec->tcp_udp.mask.dst_port));
		MLX5_SET(fte_match_set_lyr_2_4, outer_headers_v, tcp_dport,
			 ntohs(ib_spec->tcp_udp.val.dst_port));
		break;
	case IB_FLOW_SPEC_UDP:
		if (FIELDS_NOT_SUPPORTED(ib_spec->tcp_udp.mask,
					 LAST_TCP_UDP_FIELD))
			return -ENOTSUPP;

		MLX5_SET(fte_match_set_lyr_2_4, outer_headers_c, ip_protocol,
			 0xff);
		MLX5_SET(fte_match_set_lyr_2_4, outer_headers_v, ip_protocol,
			 IPPROTO_UDP);

		MLX5_SET(fte_match_set_lyr_2_4, outer_headers_c, udp_sport,
			 ntohs(ib_spec->tcp_udp.mask.src_port));
		MLX5_SET(fte_match_set_lyr_2_4, outer_headers_v, udp_sport,
			 ntohs(ib_spec->tcp_udp.val.src_port));

		MLX5_SET(fte_match_set_lyr_2_4, outer_headers_c, udp_dport,
			 ntohs(ib_spec->tcp_udp.mask.dst_port));
		MLX5_SET(fte_match_set_lyr_2_4, outer_headers_v, udp_dport,
			 ntohs(ib_spec->tcp_udp.val.dst_port));
		break;
	default:
		return -EINVAL;
	}

	return 0;
}