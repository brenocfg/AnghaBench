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
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/ * current ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_lock ; 
 int /*<<< orphan*/ * prepare_owner ; 
 scalar_t__ prepare_refcnt ; 

__attribute__((used)) static void clk_prepare_unlock(void)
{
	WARN_ON_ONCE(prepare_owner != current);
	WARN_ON_ONCE(prepare_refcnt == 0);

	if (--prepare_refcnt)
		return;
	prepare_owner = NULL;
	mutex_unlock(&prepare_lock);
}