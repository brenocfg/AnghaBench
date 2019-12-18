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
struct resource {int dummy; } ;
struct mv_cp110_icu_softc {int /*<<< orphan*/  parent; } ;
struct intr_map_data {int dummy; } ;
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int PIC_TEARDOWN_INTR (int /*<<< orphan*/ ,struct intr_irqsrc*,struct resource*,struct intr_map_data*) ; 
 struct mv_cp110_icu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct intr_map_data* mv_cp110_icu_convert_map_data (struct mv_cp110_icu_softc*,struct intr_map_data*) ; 

__attribute__((used)) static int
mv_cp110_icu_teardown_intr(device_t dev, struct intr_irqsrc *isrc,
    struct resource *res, struct intr_map_data *data)
{
	struct mv_cp110_icu_softc *sc;

	sc = device_get_softc(dev);
	data = mv_cp110_icu_convert_map_data(sc, data);
	if (data == NULL)
		return (EINVAL);

	return (PIC_TEARDOWN_INTR(sc->parent, isrc, res, data));
}