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
struct evbuffer {int refcnt; int /*<<< orphan*/  max_read; int /*<<< orphan*/  first; int /*<<< orphan*/ * last_with_datap; int /*<<< orphan*/  callbacks; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_MAX_READ_DEFAULT ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 struct evbuffer* mm_calloc (int,int) ; 

struct evbuffer *
evbuffer_new(void)
{
	struct evbuffer *buffer;

	buffer = mm_calloc(1, sizeof(struct evbuffer));
	if (buffer == NULL)
		return (NULL);

	LIST_INIT(&buffer->callbacks);
	buffer->refcnt = 1;
	buffer->last_with_datap = &buffer->first;
	buffer->max_read = EVBUFFER_MAX_READ_DEFAULT;

	return (buffer);
}