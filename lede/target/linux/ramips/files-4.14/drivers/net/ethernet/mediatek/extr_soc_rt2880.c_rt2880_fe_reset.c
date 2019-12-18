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
 int /*<<< orphan*/  RT2880_RESET_FE ; 
 int /*<<< orphan*/  fe_reset (int /*<<< orphan*/ ) ; 

void rt2880_fe_reset(void)
{
	fe_reset(RT2880_RESET_FE);
}