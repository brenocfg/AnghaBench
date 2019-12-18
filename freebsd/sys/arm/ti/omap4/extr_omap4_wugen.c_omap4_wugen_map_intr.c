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
struct omap4_wugen_sc {int /*<<< orphan*/  sc_parent; } ;
struct intr_map_data {int dummy; } ;
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PIC_MAP_INTR (int /*<<< orphan*/ ,struct intr_map_data*,struct intr_irqsrc**) ; 
 struct omap4_wugen_sc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
omap4_wugen_map_intr(device_t dev, struct intr_map_data *data,
    struct intr_irqsrc **isrcp)
{
	struct omap4_wugen_sc *sc = device_get_softc(dev);

	return (PIC_MAP_INTR(sc->sc_parent, data, isrcp));
}