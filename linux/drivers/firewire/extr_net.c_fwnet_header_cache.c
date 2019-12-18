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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int /*<<< orphan*/  addr_len; } ;
struct neighbour {int /*<<< orphan*/  ha; struct net_device* dev; } ;
struct hh_cache {int /*<<< orphan*/  hh_len; scalar_t__ hh_data; } ;
struct fwnet_header {int /*<<< orphan*/  h_dest; scalar_t__ h_proto; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_802_3 ; 
 int /*<<< orphan*/  FWNET_HLEN ; 
 int HH_DATA_OFF (int) ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fwnet_header_cache(const struct neighbour *neigh,
			      struct hh_cache *hh, __be16 type)
{
	struct net_device *net;
	struct fwnet_header *h;

	if (type == cpu_to_be16(ETH_P_802_3))
		return -1;
	net = neigh->dev;
	h = (struct fwnet_header *)((u8 *)hh->hh_data + HH_DATA_OFF(sizeof(*h)));
	h->h_proto = type;
	memcpy(h->h_dest, neigh->ha, net->addr_len);
	hh->hh_len = FWNET_HLEN;

	return 0;
}