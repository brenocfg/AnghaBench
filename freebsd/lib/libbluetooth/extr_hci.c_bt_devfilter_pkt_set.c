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
struct bt_devfilter {int /*<<< orphan*/  packet_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  bit_set (int /*<<< orphan*/ ,scalar_t__) ; 

void
bt_devfilter_pkt_set(struct bt_devfilter *filter, uint8_t type)
{
	bit_set(filter->packet_mask, type - 1);
}