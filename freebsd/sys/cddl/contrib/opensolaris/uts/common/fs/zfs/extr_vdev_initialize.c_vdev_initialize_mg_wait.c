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
struct TYPE_3__ {int /*<<< orphan*/  mg_ms_initialize_lock; int /*<<< orphan*/  mg_ms_initialize_cv; scalar_t__ mg_initialize_updating; } ;
typedef  TYPE_1__ metaslab_group_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vdev_initialize_mg_wait(metaslab_group_t *mg)
{
	ASSERT(MUTEX_HELD(&mg->mg_ms_initialize_lock));
	while (mg->mg_initialize_updating) {
		cv_wait(&mg->mg_ms_initialize_cv, &mg->mg_ms_initialize_lock);
	}
}