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
struct intr_map_data {int dummy; } ;
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
gicv3_its_map_intr(device_t dev, struct intr_map_data *data,
    struct intr_irqsrc **isrcp)
{

	/*
	 * This should never happen, we only call this function to map
	 * interrupts found before the controller driver is ready.
	 */
	panic("gicv3_its_map_intr: Unable to map a MSI interrupt");
}