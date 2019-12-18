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
typedef  int /*<<< orphan*/  u_int ;
struct firewire_softc {int /*<<< orphan*/  fc; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 scalar_t__ device_add_child (scalar_t__,char const*,int) ; 
 struct firewire_softc* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  device_probe_and_attach (scalar_t__) ; 
 int /*<<< orphan*/  device_set_ivars (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static device_t
firewire_add_child(device_t dev, u_int order, const char *name, int unit)
{
	device_t child;
	struct firewire_softc *sc;

	sc = device_get_softc(dev);
	child = device_add_child(dev, name, unit);
	if (child) {
		device_set_ivars(child, sc->fc);
		device_probe_and_attach(child);
	}

	return child;
}