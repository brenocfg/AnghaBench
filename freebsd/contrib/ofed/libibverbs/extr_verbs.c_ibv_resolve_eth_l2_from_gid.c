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
union ibv_gid {scalar_t__ raw; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct peer_address {int /*<<< orphan*/  size; int /*<<< orphan*/  address; } ;
struct in6_addr {int dummy; } ;
struct ibv_context {int dummy; } ;
struct TYPE_3__ {scalar_t__* raw; } ;
struct TYPE_4__ {TYPE_1__ dgid; int /*<<< orphan*/  sgid_index; } ;
struct ibv_ah_attr {TYPE_2__ grh; int /*<<< orphan*/  port_num; } ;
struct get_neigh_handler {int dummy; } ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int EHOSTUNREACH ; 
 int EINVAL ; 
 int ENOSYS ; 
 int ETHERNET_LL_SIZE ; 
 int /*<<< orphan*/  NEIGH_GET_DEFAULT_TIMEOUT_MS ; 
 scalar_t__ create_peer_from_gid (int,scalar_t__*,struct peer_address*) ; 
 int ibv_query_gid (struct ibv_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union ibv_gid*) ; 
 scalar_t__ ipv6_addr_v4mapped (struct in6_addr*) ; 
 int /*<<< orphan*/  neigh_free_resources (struct get_neigh_handler*) ; 
 int neigh_get_ll (struct get_neigh_handler*,int /*<<< orphan*/ *,int) ; 
 int neigh_get_oif_from_src (struct get_neigh_handler*) ; 
 int neigh_get_vlan_id_from_dev (struct get_neigh_handler*) ; 
 int neigh_init_resources (struct get_neigh_handler*,int /*<<< orphan*/ ) ; 
 scalar_t__ neigh_set_dst (struct get_neigh_handler*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neigh_set_oif (struct get_neigh_handler*,int) ; 
 scalar_t__ neigh_set_src (struct get_neigh_handler*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neigh_set_vlan_id (struct get_neigh_handler*,int) ; 
 scalar_t__ process_get_neigh (struct get_neigh_handler*) ; 

int ibv_resolve_eth_l2_from_gid(struct ibv_context *context,
				struct ibv_ah_attr *attr,
				uint8_t eth_mac[ETHERNET_LL_SIZE],
				uint16_t *vid)
{
#ifndef NRESOLVE_NEIGH
	int dst_family;
	int src_family;
	int oif;
	struct get_neigh_handler neigh_handler;
	union ibv_gid sgid;
	int ether_len;
	struct peer_address src;
	struct peer_address dst;
	uint16_t ret_vid;
	int ret = -EINVAL;
	int err;

	err = ibv_query_gid(context, attr->port_num,
			    attr->grh.sgid_index, &sgid);

	if (err)
		return err;

	err = neigh_init_resources(&neigh_handler,
				   NEIGH_GET_DEFAULT_TIMEOUT_MS);

	if (err)
		return err;

	dst_family = ipv6_addr_v4mapped((struct in6_addr *)attr->grh.dgid.raw) ?
			AF_INET : AF_INET6;
	src_family = ipv6_addr_v4mapped((struct in6_addr *)sgid.raw) ?
			AF_INET : AF_INET6;

	if (create_peer_from_gid(dst_family, attr->grh.dgid.raw, &dst))
		goto free_resources;

	if (create_peer_from_gid(src_family, &sgid.raw, &src))
		goto free_resources;

	if (neigh_set_dst(&neigh_handler, dst_family, dst.address,
			  dst.size))
		goto free_resources;

	if (neigh_set_src(&neigh_handler, src_family, src.address,
			  src.size))
		goto free_resources;

	oif = neigh_get_oif_from_src(&neigh_handler);

	if (oif > 0)
		neigh_set_oif(&neigh_handler, oif);
	else
		goto free_resources;

	ret = -EHOSTUNREACH;

	/* blocking call */
	if (process_get_neigh(&neigh_handler))
		goto free_resources;

	ret_vid = neigh_get_vlan_id_from_dev(&neigh_handler);

	if (ret_vid <= 0xfff)
		neigh_set_vlan_id(&neigh_handler, ret_vid);

	/* We are using only Ethernet here */
	ether_len = neigh_get_ll(&neigh_handler,
				 eth_mac,
				 sizeof(uint8_t) * ETHERNET_LL_SIZE);

	if (ether_len <= 0)
		goto free_resources;

	*vid = ret_vid;

	ret = 0;

free_resources:
	neigh_free_resources(&neigh_handler);

	return ret;
#else
	return -ENOSYS;
#endif
}