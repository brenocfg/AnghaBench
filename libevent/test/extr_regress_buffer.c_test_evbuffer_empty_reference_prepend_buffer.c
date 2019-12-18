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
 int /*<<< orphan*/  evbuffer_add (struct evbuffer*,char*,int) ; 
 int /*<<< orphan*/  evbuffer_add_reference (struct evbuffer*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evbuffer_free (struct evbuffer*) ; 
 struct evbuffer* evbuffer_new () ; 
 int /*<<< orphan*/  evbuffer_prepend_buffer (struct evbuffer*,struct evbuffer*) ; 
 scalar_t__ evbuffer_pullup (struct evbuffer*,int) ; 
 int /*<<< orphan*/  evbuffer_validate (struct evbuffer*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
test_evbuffer_empty_reference_prepend_buffer(void *ptr)
{
	struct evbuffer *buf1 = NULL, *buf2 = NULL;

	buf1 = evbuffer_new();
	tt_assert(buf1);
	buf2 = evbuffer_new();
	tt_assert(buf2);

	/** empty chain could leave invalid last_with_datap */
	evbuffer_add_reference(buf1, "", 0, NULL, NULL);
	evbuffer_validate(buf1);
	evbuffer_add(buf2, "foo", 3);
	evbuffer_validate(buf2);
	evbuffer_prepend_buffer(buf2, buf1);
	evbuffer_validate(buf2);

	tt_assert(!strncmp((char *)evbuffer_pullup(buf2, -1), "foo", 3));
	evbuffer_validate(buf2);

	tt_assert(!strncmp((char *)evbuffer_pullup(buf1, -1), "", 0));
	evbuffer_validate(buf2);

end:
	if (buf1)
		evbuffer_free(buf1);
	if (buf2)
		evbuffer_free(buf2);
}