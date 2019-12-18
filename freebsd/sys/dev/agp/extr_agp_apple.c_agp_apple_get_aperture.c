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
typedef  int /*<<< orphan*/  uint32_t ;
struct agp_apple_softc {int /*<<< orphan*/  aperture; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct agp_apple_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
agp_apple_get_aperture(device_t dev)
{
	struct agp_apple_softc *sc = device_get_softc(dev);

	return (sc->aperture);
}