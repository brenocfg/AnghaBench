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
typedef  int /*<<< orphan*/  uint32_t ;
struct arswitch_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR8X16_VLAN_OP_LOAD ; 
 int /*<<< orphan*/  ARSWITCH_LOCK_ASSERT (struct arswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int ar8xxx_vlan_op (struct arswitch_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
ar8xxx_set_dot1q_vlan(struct arswitch_softc *sc, uint32_t ports,
    uint32_t untagged_ports, int vid)
{
	int err;

	ARSWITCH_LOCK_ASSERT(sc, MA_OWNED);
	err = ar8xxx_vlan_op(sc, AR8X16_VLAN_OP_LOAD, vid, ports);
	if (err)
		return (err);
	return (0);
}