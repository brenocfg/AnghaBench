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
struct netmap_if {scalar_t__ ni_bufs_head; } ;
struct netmap_adapter {int /*<<< orphan*/  nm_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  netmap_extra_free (struct netmap_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  netmap_if_free (int /*<<< orphan*/ ,struct netmap_if*) ; 

__attribute__((used)) static void
netmap_mem2_if_delete(struct netmap_adapter *na, struct netmap_if *nifp)
{
	if (nifp == NULL)
		/* nothing to do */
		return;
	if (nifp->ni_bufs_head)
		netmap_extra_free(na, nifp->ni_bufs_head);
	netmap_if_free(na->nm_mem, nifp);
}