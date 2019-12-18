#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct mv_ap806_sei_softc {TYPE_1__* isrcs; } ;
struct intr_map_data {int dummy; } ;
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {struct intr_irqsrc isrc; } ;

/* Variables and functions */
 struct mv_ap806_sei_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mv_ap806_sei_map (int /*<<< orphan*/ ,struct intr_map_data*,size_t*) ; 

__attribute__((used)) static int
mv_ap806_sei_map_intr(device_t dev, struct intr_map_data *data,
    struct intr_irqsrc **isrcp)
{
	struct mv_ap806_sei_softc *sc;
	u_int irq;
	int rv;

	sc = device_get_softc(dev);
	rv = mv_ap806_sei_map(dev, data, &irq);
	if (rv == 0)
		*isrcp = &sc->isrcs[irq].isrc;

	return (rv);
}