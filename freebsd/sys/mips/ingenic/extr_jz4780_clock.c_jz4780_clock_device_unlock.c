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
struct jz4780_clock_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CGU_UNLOCK (struct jz4780_clock_softc*) ; 
 struct jz4780_clock_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
jz4780_clock_device_unlock(device_t dev)
{
	struct jz4780_clock_softc *sc;

	sc = device_get_softc(dev);
	CGU_UNLOCK(sc);
}