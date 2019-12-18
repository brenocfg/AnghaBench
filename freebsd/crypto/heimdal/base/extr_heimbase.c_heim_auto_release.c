#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct heim_base {TYPE_1__* autorelpool; } ;
struct ar_tls {TYPE_1__* current; } ;
typedef  int /*<<< orphan*/ * heim_object_t ;
typedef  TYPE_1__* heim_auto_release_t ;
struct TYPE_2__ {int /*<<< orphan*/  pool_mutex; int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIM_TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct heim_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEIM_TAILQ_REMOVE (int /*<<< orphan*/ *,struct heim_base*,int /*<<< orphan*/ ) ; 
 struct heim_base* PTR2BASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  autorel ; 
 struct ar_tls* autorel_tls () ; 
 int /*<<< orphan*/  heim_abort (char*) ; 
 scalar_t__ heim_base_is_tagged (int /*<<< orphan*/ *) ; 

void
heim_auto_release(heim_object_t ptr)
{
    struct heim_base *p = PTR2BASE(ptr);
    struct ar_tls *tls = autorel_tls();
    heim_auto_release_t ar;

    if (ptr == NULL || heim_base_is_tagged(ptr))
	return;

    /* drop from old pool */
    if ((ar = p->autorelpool) != NULL) {
	HEIMDAL_MUTEX_lock(&ar->pool_mutex);
	HEIM_TAILQ_REMOVE(&ar->pool, p, autorel);
	p->autorelpool = NULL;
	HEIMDAL_MUTEX_unlock(&ar->pool_mutex);
    }

    if (tls == NULL || (ar = tls->current) == NULL)
	heim_abort("no auto relase pool in place, would leak");

    HEIMDAL_MUTEX_lock(&ar->pool_mutex);
    HEIM_TAILQ_INSERT_HEAD(&ar->pool, p, autorel);
    p->autorelpool = ar;
    HEIMDAL_MUTEX_unlock(&ar->pool_mutex);
}