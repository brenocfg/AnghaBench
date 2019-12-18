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
struct iicbb_softc {int /*<<< orphan*/ * iicbus; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 scalar_t__ device_get_softc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
iicbb_child_detached( device_t dev, device_t child )
{
	struct iicbb_softc *sc = (struct iicbb_softc *)device_get_softc(dev);

	if (child == sc->iicbus)
		sc->iicbus = NULL;
}