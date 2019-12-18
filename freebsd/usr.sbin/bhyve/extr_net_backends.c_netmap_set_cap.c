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
typedef  int /*<<< orphan*/  uint64_t ;
struct net_backend {int dummy; } ;

/* Variables and functions */
 int netmap_set_vnet_hdr_len (struct net_backend*,unsigned int) ; 

__attribute__((used)) static int
netmap_set_cap(struct net_backend *be, uint64_t features,
	       unsigned vnet_hdr_len)
{

	return (netmap_set_vnet_hdr_len(be, vnet_hdr_len));
}