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
typedef  scalar_t__ u32 ;
struct rtl8366_smi {unsigned int gpio_sda; unsigned int gpio_sck; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_direction_input (unsigned int) ; 
 int /*<<< orphan*/  gpio_direction_output (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_get_value (unsigned int) ; 
 int /*<<< orphan*/  gpio_set_value (unsigned int,int) ; 
 int /*<<< orphan*/  rtl8366_smi_clk_delay (struct rtl8366_smi*) ; 

__attribute__((used)) static void rtl8366_smi_read_bits(struct rtl8366_smi *smi, u32 len, u32 *data)
{
	unsigned int sda = smi->gpio_sda;
	unsigned int sck = smi->gpio_sck;

	gpio_direction_input(sda);

	for (*data = 0; len > 0; len--) {
		u32 u;

		rtl8366_smi_clk_delay(smi);

		/* clocking */
		gpio_set_value(sck, 1);
		rtl8366_smi_clk_delay(smi);
		u = !!gpio_get_value(sda);
		gpio_set_value(sck, 0);

		*data |= (u << (len - 1));
	}

	gpio_direction_output(sda, 0);
}