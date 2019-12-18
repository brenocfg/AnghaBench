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
struct snapper_softc {int /*<<< orphan*/  sc_addr; void* sc_dev; } ;
typedef  void* device_t ;

/* Variables and functions */
 struct snapper_softc* device_get_softc (void*) ; 
 void* i2s_mixer ; 
 int /*<<< orphan*/ * i2s_mixer_class ; 
 int /*<<< orphan*/  iicbus_get_addr (void*) ; 
 int /*<<< orphan*/  snapper_mixer_class ; 

__attribute__((used)) static int
snapper_attach(device_t dev)
{
	struct snapper_softc *sc;
		
	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	sc->sc_addr = iicbus_get_addr(dev);

	i2s_mixer_class = &snapper_mixer_class;
	i2s_mixer = dev;

	return (0);
}