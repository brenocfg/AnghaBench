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
typedef  int /*<<< orphan*/  u_int ;
struct intr_map_data_msi {scalar_t__ isrc; } ;
struct gic_irqsrc {int /*<<< orphan*/  gi_irq; } ;
typedef  enum intr_trigger { ____Placeholder_intr_trigger } intr_trigger ;
typedef  enum intr_polarity { ____Placeholder_intr_polarity } intr_polarity ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_POLARITY_HIGH ; 
 int INTR_TRIGGER_EDGE ; 

__attribute__((used)) static int
gic_map_msi(device_t dev, struct intr_map_data_msi *msi_data, u_int *irqp,
    enum intr_polarity *polp, enum intr_trigger *trigp)
{
	struct gic_irqsrc *gi;

	/* Map a non-GICv2m MSI */
	gi = (struct gic_irqsrc *)msi_data->isrc;
	if (gi == NULL)
		return (ENXIO);

	*irqp = gi->gi_irq;

	/* MSI/MSI-X interrupts are always edge triggered with high polarity */
	*polp = INTR_POLARITY_HIGH;
	*trigp = INTR_TRIGGER_EDGE;

	return (0);
}