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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct bridge_softc {int dummy; } ;
struct bridge_rtnode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_LOCK_ASSERT (struct bridge_softc*) ; 
 int ENOENT ; 
 int /*<<< orphan*/  bridge_rtnode_destroy (struct bridge_softc*,struct bridge_rtnode*) ; 
 struct bridge_rtnode* bridge_rtnode_lookup (struct bridge_softc*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bridge_rtdaddr(struct bridge_softc *sc, const uint8_t *addr, uint16_t vlan)
{
	struct bridge_rtnode *brt;
	int found = 0;

	BRIDGE_LOCK_ASSERT(sc);

	/*
	 * If vlan is zero then we want to delete for all vlans so the lookup
	 * may return more than one.
	 */
	while ((brt = bridge_rtnode_lookup(sc, addr, vlan)) != NULL) {
		bridge_rtnode_destroy(sc, brt);
		found = 1;
	}

	return (found ? 0 : ENOENT);
}