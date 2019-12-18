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
typedef  int /*<<< orphan*/  u8 ;
struct ts_nbus {struct gpio_descs* data; } ;
struct gpio_descs {int /*<<< orphan*/  info; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_BITMAP (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gpiod_set_array_value_cansleep (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * values ; 

__attribute__((used)) static void ts_nbus_write_byte(struct ts_nbus *ts_nbus, u8 byte)
{
	struct gpio_descs *gpios = ts_nbus->data;
	DECLARE_BITMAP(values, 8);

	values[0] = byte;

	gpiod_set_array_value_cansleep(8, gpios->desc, gpios->info, values);
}