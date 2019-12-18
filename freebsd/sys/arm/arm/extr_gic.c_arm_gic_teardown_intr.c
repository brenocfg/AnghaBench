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
struct intr_map_data {int dummy; } ;
struct intr_irqsrc {scalar_t__ isrc_handlers; } ;
struct gic_irqsrc {int gi_flags; int /*<<< orphan*/  gi_trig; int /*<<< orphan*/  gi_pol; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int GI_FLAG_MSI ; 
 int /*<<< orphan*/  INTR_POLARITY_CONFORM ; 
 int /*<<< orphan*/  INTR_TRIGGER_CONFORM ; 

__attribute__((used)) static int
arm_gic_teardown_intr(device_t dev, struct intr_irqsrc *isrc,
    struct resource *res, struct intr_map_data *data)
{
	struct gic_irqsrc *gi = (struct gic_irqsrc *)isrc;

	if (isrc->isrc_handlers == 0 && (gi->gi_flags & GI_FLAG_MSI) == 0) {
		gi->gi_pol = INTR_POLARITY_CONFORM;
		gi->gi_trig = INTR_TRIGGER_CONFORM;
	}
	return (0);
}