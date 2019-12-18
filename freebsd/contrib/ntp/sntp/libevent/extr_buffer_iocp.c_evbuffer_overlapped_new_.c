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
struct evbuffer {int refcnt; int is_overlapped; int /*<<< orphan*/  first; int /*<<< orphan*/ * last_with_datap; int /*<<< orphan*/  callbacks; } ;
struct evbuffer_overlapped {struct evbuffer buffer; int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 struct evbuffer_overlapped* mm_calloc (int,int) ; 

struct evbuffer *
evbuffer_overlapped_new_(evutil_socket_t fd)
{
	struct evbuffer_overlapped *evo;

	evo = mm_calloc(1, sizeof(struct evbuffer_overlapped));
	if (!evo)
		return NULL;

	LIST_INIT(&evo->buffer.callbacks);
	evo->buffer.refcnt = 1;
	evo->buffer.last_with_datap = &evo->buffer.first;

	evo->buffer.is_overlapped = 1;
	evo->fd = fd;

	return &evo->buffer;
}