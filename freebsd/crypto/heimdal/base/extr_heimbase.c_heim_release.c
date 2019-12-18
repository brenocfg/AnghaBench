#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct heim_base {scalar_t__ ref_cnt; TYPE_1__* isa; TYPE_2__* autorelpool; } ;
typedef  int heim_base_atomic_type ;
typedef  TYPE_2__* heim_auto_release_t ;
struct TYPE_4__ {int /*<<< orphan*/  pool_mutex; int /*<<< orphan*/  pool; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* dealloc ) (void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIM_TAILQ_REMOVE (int /*<<< orphan*/ *,struct heim_base*,int /*<<< orphan*/ ) ; 
 struct heim_base* PTR2BASE (void*) ; 
 int /*<<< orphan*/  autorel ; 
 int /*<<< orphan*/  free (struct heim_base*) ; 
 int /*<<< orphan*/  heim_abort (char*) ; 
 int heim_base_atomic_dec (scalar_t__*) ; 
 scalar_t__ heim_base_atomic_max ; 
 scalar_t__ heim_base_is_tagged (void*) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

void
heim_release(void *ptr)
{
    heim_base_atomic_type old;
    struct heim_base *p = PTR2BASE(ptr);

    if (ptr == NULL || heim_base_is_tagged(ptr))
	return;

    if (p->ref_cnt == heim_base_atomic_max)
	return;

    old = heim_base_atomic_dec(&p->ref_cnt) + 1;

    if (old > 1)
	return;

    if (old == 1) {
	heim_auto_release_t ar = p->autorelpool;
	/* remove from autorel pool list */
	if (ar) {
	    p->autorelpool = NULL;
	    HEIMDAL_MUTEX_lock(&ar->pool_mutex);
	    HEIM_TAILQ_REMOVE(&ar->pool, p, autorel);
	    HEIMDAL_MUTEX_unlock(&ar->pool_mutex);
	}
	if (p->isa->dealloc)
	    p->isa->dealloc(ptr);
	free(p);
    } else
	heim_abort("over release");
}