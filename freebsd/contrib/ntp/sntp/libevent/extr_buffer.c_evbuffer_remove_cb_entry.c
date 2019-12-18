#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct evbuffer_cb_entry {int dummy; } ;
struct evbuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_LOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  EVBUFFER_UNLOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct evbuffer_cb_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_free (struct evbuffer_cb_entry*) ; 
 int /*<<< orphan*/  next ; 

int
evbuffer_remove_cb_entry(struct evbuffer *buffer,
			 struct evbuffer_cb_entry *ent)
{
	EVBUFFER_LOCK(buffer);
	LIST_REMOVE(ent, next);
	EVBUFFER_UNLOCK(buffer);
	mm_free(ent);
	return 0;
}