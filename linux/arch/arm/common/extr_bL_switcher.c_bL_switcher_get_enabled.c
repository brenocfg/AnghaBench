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
 int /*<<< orphan*/  bL_switcher_activation_lock ; 
 int bL_switcher_active ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

bool bL_switcher_get_enabled(void)
{
	mutex_lock(&bL_switcher_activation_lock);

	return bL_switcher_active;
}