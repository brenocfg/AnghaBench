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
 int /*<<< orphan*/  MIN_READY_MARK ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  own_pool_ready ; 
 int /*<<< orphan*/  random_write_entropy () ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void random_mark_pool_ready(void)
{
	own_pool_ready++;
	wpa_printf(MSG_DEBUG, "random: Mark internal entropy pool to be "
		   "ready (count=%u/%u)", own_pool_ready, MIN_READY_MARK);
	random_write_entropy();
}