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
typedef  scalar_t__ uint64_t ;
struct net_backend {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
tap_set_cap(struct net_backend *be, uint64_t features,
		unsigned vnet_hdr_len)
{

	return ((features || vnet_hdr_len) ? -1 : 0);
}