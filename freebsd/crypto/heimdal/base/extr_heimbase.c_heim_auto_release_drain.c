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
typedef  int /*<<< orphan*/  heim_object_t ;
typedef  TYPE_1__* heim_auto_release_t ;
struct TYPE_3__ {int /*<<< orphan*/  pool_mutex; int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  BASE2PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIM_TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIM_TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heim_release (int /*<<< orphan*/ ) ; 

void
heim_auto_release_drain(heim_auto_release_t autorel)
{
    heim_object_t obj;

    /* release all elements on the tail queue */

    HEIMDAL_MUTEX_lock(&autorel->pool_mutex);
    while(!HEIM_TAILQ_EMPTY(&autorel->pool)) {
	obj = HEIM_TAILQ_FIRST(&autorel->pool);
	HEIMDAL_MUTEX_unlock(&autorel->pool_mutex);
	heim_release(BASE2PTR(obj));
	HEIMDAL_MUTEX_lock(&autorel->pool_mutex);
    }
    HEIMDAL_MUTEX_unlock(&autorel->pool_mutex);
}