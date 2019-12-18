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
 int /*<<< orphan*/  SWITCH_CMD_GET_SWITCH ; 
 int /*<<< orphan*/  list_switch ; 
 int /*<<< orphan*/  swlib_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swlib_priv_free () ; 
 scalar_t__ swlib_priv_init () ; 

void
swlib_list(void)
{
	if (swlib_priv_init() < 0)
		return;
	swlib_call(SWITCH_CMD_GET_SWITCH, list_switch, NULL, NULL);
	swlib_priv_free();
}