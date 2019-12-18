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
struct ds1672_softc {int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  clock_register (int /*<<< orphan*/ ,int) ; 
 struct ds1672_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int ds1672_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ds1672_attach(device_t dev)
{
	struct ds1672_softc *sc = device_get_softc(dev);
	int error;

	sc->sc_dev = dev;
	error = ds1672_init(dev);
	if (error)
		return (error);
	clock_register(dev, 1000);
	return (0);
}