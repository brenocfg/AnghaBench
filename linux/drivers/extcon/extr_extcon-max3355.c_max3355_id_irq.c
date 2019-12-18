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
struct max3355_data {int /*<<< orphan*/  edev; int /*<<< orphan*/  id_gpiod; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXTCON_USB ; 
 int /*<<< orphan*/  EXTCON_USB_HOST ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  extcon_set_state_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int gpiod_get_value_cansleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t max3355_id_irq(int irq, void *dev_id)
{
	struct max3355_data *data = dev_id;
	int id = gpiod_get_value_cansleep(data->id_gpiod);

	if (id) {
		/*
		 * ID = 1 means USB HOST cable detached.
		 * As we don't have event for USB peripheral cable attached,
		 * we simulate USB peripheral attach here.
		 */
		extcon_set_state_sync(data->edev, EXTCON_USB_HOST, false);
		extcon_set_state_sync(data->edev, EXTCON_USB, true);
	} else {
		/*
		 * ID = 0 means USB HOST cable attached.
		 * As we don't have event for USB peripheral cable detached,
		 * we simulate USB peripheral detach here.
		 */
		extcon_set_state_sync(data->edev, EXTCON_USB, false);
		extcon_set_state_sync(data->edev, EXTCON_USB_HOST, true);
	}

	return IRQ_HANDLED;
}