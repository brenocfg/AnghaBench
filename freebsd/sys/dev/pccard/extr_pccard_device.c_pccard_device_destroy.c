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
struct pccard_softc {scalar_t__ cisdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_dev (scalar_t__) ; 

int
pccard_device_destroy(struct pccard_softc *sc)
{
	if (sc->cisdev)
		destroy_dev(sc->cisdev);
	return (0);
}