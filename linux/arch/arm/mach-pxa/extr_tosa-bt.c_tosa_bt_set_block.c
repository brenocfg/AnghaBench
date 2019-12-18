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
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  tosa_bt_off (void*) ; 
 int /*<<< orphan*/  tosa_bt_on (void*) ; 

__attribute__((used)) static int tosa_bt_set_block(void *data, bool blocked)
{
	pr_info("BT_RADIO going: %s\n", blocked ? "off" : "on");

	if (!blocked) {
		pr_info("TOSA_BT: going ON\n");
		tosa_bt_on(data);
	} else {
		pr_info("TOSA_BT: going OFF\n");
		tosa_bt_off(data);
	}

	return 0;
}