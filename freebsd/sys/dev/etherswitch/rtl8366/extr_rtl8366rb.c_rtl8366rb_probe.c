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
struct rtl8366rb_softc {scalar_t__ chip_type; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 scalar_t__ RTL8366RB ; 
 int /*<<< orphan*/  bzero (struct rtl8366rb_softc*,int) ; 
 struct rtl8366rb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ smi_probe (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rtl8366rb_probe(device_t dev)
{
	struct rtl8366rb_softc *sc;

	sc = device_get_softc(dev);

	bzero(sc, sizeof(*sc));
	if (smi_probe(dev) != 0)
		return (ENXIO);
	if (sc->chip_type == RTL8366RB)
		device_set_desc(dev, "RTL8366RB Ethernet Switch Controller");
	else
		device_set_desc(dev, "RTL8366SR Ethernet Switch Controller");
	return (BUS_PROBE_DEFAULT);
}