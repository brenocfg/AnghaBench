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
struct ts_nbus {TYPE_1__* data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * desc; } ;

/* Variables and functions */
 int TS_NBUS_DIRECTION_IN ; 
 int /*<<< orphan*/  gpiod_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_direction_output (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ts_nbus_set_direction(struct ts_nbus *ts_nbus, int direction)
{
	int i;

	for (i = 0; i < 8; i++) {
		if (direction == TS_NBUS_DIRECTION_IN)
			gpiod_direction_input(ts_nbus->data->desc[i]);
		else
			/* when used as output the default state of the data
			 * lines are set to high */
			gpiod_direction_output(ts_nbus->data->desc[i], 1);
	}
}