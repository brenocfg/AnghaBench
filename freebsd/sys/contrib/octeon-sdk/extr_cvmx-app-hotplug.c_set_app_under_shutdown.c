#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int app_under_shutdown; int /*<<< orphan*/  hotplug_global_lock; } ;
typedef  TYPE_1__ cvmx_app_hotplug_global_t ;

/* Variables and functions */
 TYPE_1__* cvmx_app_get_hotplug_global_ptr () ; 
 int /*<<< orphan*/  cvmx_spinlock_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvmx_spinlock_unlock (int /*<<< orphan*/ *) ; 

void set_app_under_shutdown(int val)
{
    cvmx_app_hotplug_global_t *hgp;

    hgp = cvmx_app_get_hotplug_global_ptr();
    cvmx_spinlock_lock(&hgp->hotplug_global_lock);
    hgp->app_under_shutdown = val;
    cvmx_spinlock_unlock(&hgp->hotplug_global_lock);
}