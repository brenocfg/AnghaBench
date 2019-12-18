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
struct rtl8366_smi {unsigned int gpio_sda; unsigned int gpio_sck; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_direction_input (unsigned int) ; 
 int /*<<< orphan*/  gpio_set_value (unsigned int,int) ; 
 int /*<<< orphan*/  rtl8366_smi_clk_delay (struct rtl8366_smi*) ; 

__attribute__((used)) static void rtl8366_smi_stop(struct rtl8366_smi *smi)
{
	unsigned int sda = smi->gpio_sda;
	unsigned int sck = smi->gpio_sck;

	rtl8366_smi_clk_delay(smi);
	gpio_set_value(sda, 0);
	gpio_set_value(sck, 1);
	rtl8366_smi_clk_delay(smi);
	gpio_set_value(sda, 1);
	rtl8366_smi_clk_delay(smi);
	gpio_set_value(sck, 1);
	rtl8366_smi_clk_delay(smi);
	gpio_set_value(sck, 0);
	rtl8366_smi_clk_delay(smi);
	gpio_set_value(sck, 1);

	/* add a click */
	rtl8366_smi_clk_delay(smi);
	gpio_set_value(sck, 0);
	rtl8366_smi_clk_delay(smi);
	gpio_set_value(sck, 1);

	/* set GPIO pins to input mode */
	gpio_direction_input(sda);
	gpio_direction_input(sck);
}