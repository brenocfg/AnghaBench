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
struct net_backend {int be_vnet_hdr_len; } ;

/* Variables and functions */
 int netmap_set_vnet_hdr_len (struct net_backend*,int) ; 

__attribute__((used)) static int
netmap_has_vnet_hdr_len(struct net_backend *be, unsigned vnet_hdr_len)
{
	int prev_hdr_len = be->be_vnet_hdr_len;
	int ret;

	if (vnet_hdr_len == prev_hdr_len) {
		return (1);
	}

	ret = netmap_set_vnet_hdr_len(be, vnet_hdr_len);
	if (ret) {
		return (0);
	}

	netmap_set_vnet_hdr_len(be, prev_hdr_len);

	return (1);
}