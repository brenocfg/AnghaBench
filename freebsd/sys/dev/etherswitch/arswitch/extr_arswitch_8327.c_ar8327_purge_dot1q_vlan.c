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
 int /*<<< orphan*/  AR8327_VTU_FUNC1_OP_PURGE ; 
 int ar8327_vlan_op (struct arswitch_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ar8327_purge_dot1q_vlan(struct arswitch_softc *sc, int vid)
{

	return (ar8327_vlan_op(sc, AR8327_VTU_FUNC1_OP_PURGE, vid, 0));
}