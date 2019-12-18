#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ts_nbus {int /*<<< orphan*/  ale; int /*<<< orphan*/  strobe; int /*<<< orphan*/  csn; TYPE_1__* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  info; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_BITMAP (scalar_t__*,int) ; 
 int /*<<< orphan*/  gpiod_set_array_value_cansleep (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* values ; 

__attribute__((used)) static void ts_nbus_reset_bus(struct ts_nbus *ts_nbus)
{
	DECLARE_BITMAP(values, 8);

	values[0] = 0;

	gpiod_set_array_value_cansleep(8, ts_nbus->data->desc,
				       ts_nbus->data->info, values);
	gpiod_set_value_cansleep(ts_nbus->csn, 0);
	gpiod_set_value_cansleep(ts_nbus->strobe, 0);
	gpiod_set_value_cansleep(ts_nbus->ale, 0);
}