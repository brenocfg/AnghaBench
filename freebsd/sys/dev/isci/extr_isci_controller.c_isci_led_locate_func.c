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
struct ISCI_PHY {int led_locate; int index; int /*<<< orphan*/  led_fault; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  scic_sgpio_update_led_state (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isci_led_locate_func(void *priv, int onoff)
{
	struct ISCI_PHY *phy = priv;

	/* map onoff to the locate LED */
	phy->led_locate = onoff;
	scic_sgpio_update_led_state(phy->handle, 1 << phy->index, 
		phy->led_fault, phy->led_locate, 0);
}