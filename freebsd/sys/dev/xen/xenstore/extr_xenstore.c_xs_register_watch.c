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
typedef  int /*<<< orphan*/  watch ;
struct xs_watch {int /*<<< orphan*/  node; } ;
struct TYPE_2__ {int /*<<< orphan*/  registered_watches_lock; int /*<<< orphan*/  registered_watches; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct xs_watch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct xs_watch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_watch (char*) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 
 TYPE_1__ xs ; 
 int xs_watch (int /*<<< orphan*/ ,char*) ; 

int
xs_register_watch(struct xs_watch *watch)
{
	/* Pointer in ascii is the token. */
	char token[sizeof(watch) * 2 + 1];
	int error;

	sprintf(token, "%lX", (long)watch);

	mtx_lock(&xs.registered_watches_lock);
	KASSERT(find_watch(token) == NULL, ("watch already registered"));
	LIST_INSERT_HEAD(&xs.registered_watches, watch, list);
	mtx_unlock(&xs.registered_watches_lock);

	error = xs_watch(watch->node, token);

	/* Ignore errors due to multiple registration. */
	if (error == EEXIST)
		error = 0;

	if (error != 0) {
		mtx_lock(&xs.registered_watches_lock);
		LIST_REMOVE(watch, list);
		mtx_unlock(&xs.registered_watches_lock);
	}

	return (error);
}