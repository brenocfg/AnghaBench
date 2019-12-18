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
struct agp_softc {scalar_t__ as_state; } ;
typedef  enum agp_acquire_state { ____Placeholder_agp_acquire_state } agp_acquire_state ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ AGP_ACQUIRE_FREE ; 
 int EBUSY ; 
 struct agp_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
agp_release_helper(device_t dev, enum agp_acquire_state state)
{
	struct agp_softc *sc = device_get_softc(dev);

	if (sc->as_state == AGP_ACQUIRE_FREE)
		return 0;

	if (sc->as_state != state)
		return EBUSY;

	sc->as_state = AGP_ACQUIRE_FREE;
	return 0;
}