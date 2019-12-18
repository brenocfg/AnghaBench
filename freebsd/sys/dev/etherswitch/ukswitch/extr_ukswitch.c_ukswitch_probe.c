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
struct ukswitch_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int /*<<< orphan*/  bzero (struct ukswitch_softc*,int) ; 
 struct ukswitch_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ukswitch_probe(device_t dev)
{
	struct ukswitch_softc *sc;

	sc = device_get_softc(dev);
	bzero(sc, sizeof(*sc));

	device_set_desc_copy(dev, "Generic MDIO switch driver");
	return (BUS_PROBE_DEFAULT);
}