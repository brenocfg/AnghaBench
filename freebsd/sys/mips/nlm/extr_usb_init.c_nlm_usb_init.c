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
 int /*<<< orphan*/  nlm_usb_hw_reset (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlm_usb_intr_en (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
nlm_usb_init(void)
{
	/* XXX: should be checking if these are in Device mode here */
	printf("Initialize USB Interface\n");
	nlm_usb_hw_reset(0, 0);
	nlm_usb_hw_reset(0, 3);

	/* Enable PHY interrupts */
	nlm_usb_intr_en(0, 0);
	nlm_usb_intr_en(0, 3);
}