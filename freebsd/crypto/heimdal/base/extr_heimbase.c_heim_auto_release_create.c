#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct heim_auto_release {int dummy; } ;
struct ar_tls {int /*<<< orphan*/  tls_mutex; TYPE_1__* current; TYPE_1__* head; } ;
typedef  TYPE_1__* heim_auto_release_t ;
struct TYPE_4__ {struct TYPE_4__* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* _heim_alloc_object (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _heim_autorel_object ; 
 struct ar_tls* autorel_tls () ; 
 int /*<<< orphan*/  heim_abort (char*) ; 

heim_auto_release_t
heim_auto_release_create(void)
{
    struct ar_tls *tls = autorel_tls();
    heim_auto_release_t ar;

    if (tls == NULL)
	heim_abort("Failed to create/get autorelease head");

    ar = _heim_alloc_object(&_heim_autorel_object, sizeof(struct heim_auto_release));
    if (ar) {
	HEIMDAL_MUTEX_lock(&tls->tls_mutex);
	if (tls->head == NULL)
	    tls->head = ar;
	ar->parent = tls->current;
	tls->current = ar;
	HEIMDAL_MUTEX_unlock(&tls->tls_mutex);
    }

    return ar;
}