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
struct netmap_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netmap_free_rings (struct netmap_adapter*) ; 

__attribute__((used)) static void
netmap_mem2_rings_delete(struct netmap_adapter *na)
{
	/* last instance, release bufs and rings */
	netmap_free_rings(na);
}