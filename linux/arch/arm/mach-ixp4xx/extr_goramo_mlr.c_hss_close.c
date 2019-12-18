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
 int /*<<< orphan*/  CONTROL_HSS0_DTR_N ; 
 int /*<<< orphan*/  CONTROL_HSS1_DTR_N ; 
 int /*<<< orphan*/  GPIO_HSS0_DCD_N ; 
 int /*<<< orphan*/  GPIO_HSS0_RTS_N ; 
 int /*<<< orphan*/  GPIO_HSS1_DCD_N ; 
 int /*<<< orphan*/  GPIO_HSS1_RTS_N ; 
 int /*<<< orphan*/  IXP4XX_GPIO_IRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  output_control () ; 
 int /*<<< orphan*/ ** set_carrier_cb_tab ; 
 int /*<<< orphan*/  set_control (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hss_close(int port, void *pdev)
{
	free_irq(port ? IXP4XX_GPIO_IRQ(GPIO_HSS1_DCD_N) :
		 IXP4XX_GPIO_IRQ(GPIO_HSS0_DCD_N), pdev);
	set_carrier_cb_tab[!!port] = NULL; /* catch bugs */

	set_control(port ? CONTROL_HSS1_DTR_N : CONTROL_HSS0_DTR_N, 1);
	output_control();
	gpio_set_value(port ? GPIO_HSS1_RTS_N : GPIO_HSS0_RTS_N, 1);
}