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
struct vtmmio_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct vtmmio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int vtmmio_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtmmio_setup_platform (int /*<<< orphan*/ ,struct vtmmio_softc*) ; 

__attribute__((used)) static int
vtmmio_fdt_attach(device_t dev)
{
	struct vtmmio_softc *sc;

	sc = device_get_softc(dev);
	vtmmio_setup_platform(dev, sc);

	return (vtmmio_attach(dev));
}