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
struct TYPE_2__ {int /*<<< orphan*/  cb_func; } ;
struct evbuffer_cb_entry {int /*<<< orphan*/  flags; void* cbarg; TYPE_1__ cb; } ;
struct evbuffer {int /*<<< orphan*/  callbacks; } ;
typedef  int /*<<< orphan*/  evbuffer_cb_func ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_CB_ENABLED ; 
 int /*<<< orphan*/  EVBUFFER_LOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  EVBUFFER_UNLOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct evbuffer_cb_entry*,int /*<<< orphan*/ ) ; 
 struct evbuffer_cb_entry* mm_calloc (int,int) ; 
 int /*<<< orphan*/  next ; 

struct evbuffer_cb_entry *
evbuffer_add_cb(struct evbuffer *buffer, evbuffer_cb_func cb, void *cbarg)
{
	struct evbuffer_cb_entry *e;
	if (! (e = mm_calloc(1, sizeof(struct evbuffer_cb_entry))))
		return NULL;
	EVBUFFER_LOCK(buffer);
	e->cb.cb_func = cb;
	e->cbarg = cbarg;
	e->flags = EVBUFFER_CB_ENABLED;
	LIST_INSERT_HEAD(&buffer->callbacks, e, next);
	EVBUFFER_UNLOCK(buffer);
	return e;
}