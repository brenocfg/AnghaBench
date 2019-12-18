#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int spa_mode; int spa_async_suspended; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  spa_activate (TYPE_1__*,int) ; 
 int /*<<< orphan*/  spa_deactivate (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_unload (TYPE_1__*) ; 

__attribute__((used)) static void
spa_ld_prepare_for_reload(spa_t *spa)
{
	int mode = spa->spa_mode;
	int async_suspended = spa->spa_async_suspended;

	spa_unload(spa);
	spa_deactivate(spa);
	spa_activate(spa, mode);

	/*
	 * We save the value of spa_async_suspended as it gets reset to 0 by
	 * spa_unload(). We want to restore it back to the original value before
	 * returning as we might be calling spa_async_resume() later.
	 */
	spa->spa_async_suspended = async_suspended;
}