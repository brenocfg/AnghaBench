#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ifvlantrunk {TYPE_1__* parent; } ;
struct TYPE_2__ {int /*<<< orphan*/ * if_vlantrunk; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_VLAN ; 
 int /*<<< orphan*/  TRUNK_LOCK_DESTROY (struct ifvlantrunk*) ; 
 int /*<<< orphan*/  VLAN_XLOCK_ASSERT () ; 
 int /*<<< orphan*/  free (struct ifvlantrunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_rele (TYPE_1__*) ; 
 int /*<<< orphan*/  vlan_freehash (struct ifvlantrunk*) ; 

__attribute__((used)) static void
trunk_destroy(struct ifvlantrunk *trunk)
{
	VLAN_XLOCK_ASSERT();

	vlan_freehash(trunk);
	trunk->parent->if_vlantrunk = NULL;
	TRUNK_LOCK_DESTROY(trunk);
	if_rele(trunk->parent);
	free(trunk, M_VLAN);
}