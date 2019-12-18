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
struct nm_generic_mit {int mit_ring_idx; struct netmap_adapter* mit_na; scalar_t__ mit_pending; } ;
struct netmap_adapter {int dummy; } ;

/* Variables and functions */

void
nm_os_mitigation_init(struct nm_generic_mit *mit, int idx, struct netmap_adapter *na)
{
	mit->mit_pending = 0;
	mit->mit_ring_idx = idx;
	mit->mit_na = na;
}