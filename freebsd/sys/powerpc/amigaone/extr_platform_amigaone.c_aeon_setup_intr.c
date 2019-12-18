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

/* Variables and functions */
 int /*<<< orphan*/  INTR_POLARITY_LOW ; 
 int /*<<< orphan*/  INTR_TRIGGER_EDGE ; 
 int /*<<< orphan*/  INTR_TYPE_MISC ; 
 int MAP_IRQ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  aeon_pbutton_intr ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  is_aeon ; 
 int /*<<< orphan*/  powerpc_config_intr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powerpc_setup_intr (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
aeon_setup_intr(void *unused)
{
	int irq;

	if (!is_aeon)
		return;

	if (bootverbose)
		printf("Configuring AmigaOne power button.\n");

	irq = 4; /* From TRM, IRQ4 is raised when power button is pressed. */

	/* Get us the root PIC. */
	irq = MAP_IRQ(0, irq);
	powerpc_config_intr(irq, INTR_TRIGGER_EDGE, INTR_POLARITY_LOW);
	powerpc_setup_intr("power_button", irq, NULL, aeon_pbutton_intr, NULL,
	    INTR_TYPE_MISC, NULL, 0);
}