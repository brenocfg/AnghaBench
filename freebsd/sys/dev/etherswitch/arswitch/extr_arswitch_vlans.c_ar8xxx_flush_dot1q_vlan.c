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
struct arswitch_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR8X16_VLAN_OP_FLUSH ; 
 int /*<<< orphan*/  ARSWITCH_LOCK_ASSERT (struct arswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int ar8xxx_vlan_op (struct arswitch_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ar8xxx_flush_dot1q_vlan(struct arswitch_softc *sc)
{

	ARSWITCH_LOCK_ASSERT(sc, MA_OWNED);
	return (ar8xxx_vlan_op(sc, AR8X16_VLAN_OP_FLUSH, 0, 0));
}