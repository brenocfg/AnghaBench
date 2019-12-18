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
struct hdac_softc {int /*<<< orphan*/  unsol_registered; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct hdac_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdac_poll_reinit (struct hdac_softc*) ; 

__attribute__((used)) static void
hdac_unsol_free(device_t dev, device_t child, int tag)
{
	struct hdac_softc *sc = device_get_softc(dev);

	sc->unsol_registered--;
	hdac_poll_reinit(sc);
}