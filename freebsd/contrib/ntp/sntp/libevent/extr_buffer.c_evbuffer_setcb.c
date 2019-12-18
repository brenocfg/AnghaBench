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
struct TYPE_2__ {scalar_t__ cb_obsolete; } ;
struct evbuffer_cb_entry {int /*<<< orphan*/  flags; TYPE_1__ cb; } ;
struct evbuffer {int /*<<< orphan*/  callbacks; } ;
typedef  scalar_t__ evbuffer_cb ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_CB_OBSOLETE ; 
 int /*<<< orphan*/  EVBUFFER_LOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  EVBUFFER_UNLOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct evbuffer_cb_entry* evbuffer_add_cb (struct evbuffer*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  evbuffer_remove_all_callbacks (struct evbuffer*) ; 

void
evbuffer_setcb(struct evbuffer *buffer, evbuffer_cb cb, void *cbarg)
{
	EVBUFFER_LOCK(buffer);

	if (!LIST_EMPTY(&buffer->callbacks))
		evbuffer_remove_all_callbacks(buffer);

	if (cb) {
		struct evbuffer_cb_entry *ent =
		    evbuffer_add_cb(buffer, NULL, cbarg);
		ent->cb.cb_obsolete = cb;
		ent->flags |= EVBUFFER_CB_OBSOLETE;
	}
	EVBUFFER_UNLOCK(buffer);
}