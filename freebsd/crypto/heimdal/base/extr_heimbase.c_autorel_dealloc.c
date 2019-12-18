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
struct ar_tls {void* current; void* head; int /*<<< orphan*/  tls_mutex; } ;
typedef  TYPE_1__* heim_auto_release_t ;
struct TYPE_3__ {void* parent; int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIM_TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct ar_tls* autorel_tls () ; 
 int /*<<< orphan*/  heim_abort (char*) ; 
 int /*<<< orphan*/  heim_auto_release_drain (TYPE_1__*) ; 

__attribute__((used)) static void
autorel_dealloc(void *ptr)
{
    heim_auto_release_t ar = ptr;
    struct ar_tls *tls;

    tls = autorel_tls();
    if (tls == NULL)
	heim_abort("autorelease pool released on thread w/o autorelease inited");

    heim_auto_release_drain(ar);

    if (!HEIM_TAILQ_EMPTY(&ar->pool))
	heim_abort("pool not empty after draining");

    HEIMDAL_MUTEX_lock(&tls->tls_mutex);
    if (tls->current != ptr)
	heim_abort("autorelease not releaseing top pool");

    if (tls->current != tls->head)
	tls->current = ar->parent;
    HEIMDAL_MUTEX_unlock(&tls->tls_mutex);
}