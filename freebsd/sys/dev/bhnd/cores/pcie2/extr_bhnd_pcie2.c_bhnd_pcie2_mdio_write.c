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
struct bhnd_pcie2_softc {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 

int
bhnd_pcie2_mdio_write(struct bhnd_pcie2_softc *sc, int phy, int reg, int val)
{
	// TODO
	return (ENXIO);
}