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
typedef  int /*<<< orphan*/  etherswitch_vlangroup_t ;

/* Variables and functions */
 int ar8xxx_setvgroup (struct arswitch_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ar8327_vlan_setvgroup(struct arswitch_softc *sc, etherswitch_vlangroup_t *vg)
{

	return (ar8xxx_setvgroup(sc, vg));
}