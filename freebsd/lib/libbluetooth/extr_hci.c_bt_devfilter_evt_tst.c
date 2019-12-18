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
typedef  scalar_t__ uint8_t ;
struct bt_devfilter {int /*<<< orphan*/  event_mask; } ;

/* Variables and functions */
 int bit_test (int /*<<< orphan*/ ,scalar_t__) ; 

int
bt_devfilter_evt_tst(struct bt_devfilter const *filter, uint8_t event)
{
	return (bit_test(filter->event_mask, event - 1));
}