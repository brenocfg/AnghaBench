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
typedef  scalar_t__ uint32_t ;
struct mv_gpio_softc {scalar_t__ offset; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
mv_gpio_reg_read(device_t dev, uint32_t reg)
{
	struct mv_gpio_softc *sc;
	sc = (struct mv_gpio_softc *)device_get_softc(dev);

	return (bus_space_read_4(sc->bst, sc->bsh, sc->offset + reg));
}