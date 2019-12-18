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
struct evbuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  evbuffer_add_reference (struct evbuffer*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evbuffer_free (struct evbuffer*) ; 
 struct evbuffer* evbuffer_new () ; 
 int /*<<< orphan*/  evbuffer_prepend (struct evbuffer*,char*,int) ; 
 scalar_t__ evbuffer_pullup (struct evbuffer*,int) ; 
 int /*<<< orphan*/  evbuffer_validate (struct evbuffer*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
test_evbuffer_empty_reference_prepend(void *ptr)
{
	struct evbuffer *buf = NULL;

	buf = evbuffer_new();
	tt_assert(buf);

	/** empty chain could leave invalid last_with_datap */
	evbuffer_add_reference(buf, "", 0, NULL, NULL);
	evbuffer_validate(buf);
	evbuffer_prepend(buf, "foo", 3);

	evbuffer_validate(buf);
	tt_assert(!strncmp((char *)evbuffer_pullup(buf, -1), "foo", 3));
	evbuffer_validate(buf);

end:
	if (buf)
		evbuffer_free(buf);
}