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
typedef  int /*<<< orphan*/  u_char ;
struct evbuffer {int dummy; } ;

/* Variables and functions */
 int EVBUFFER_INITIAL_LENGTH ; 
 int /*<<< orphan*/  evbuffer_add (struct evbuffer*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  evbuffer_drain (struct evbuffer*,int) ; 
 int /*<<< orphan*/ * evbuffer_find (struct evbuffer*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  evbuffer_free (struct evbuffer*) ; 
 struct evbuffer* evbuffer_new () ; 
 int /*<<< orphan*/  evbuffer_validate (struct evbuffer*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  tt_assert (struct evbuffer*) ; 
 int /*<<< orphan*/  tt_want (int) ; 

__attribute__((used)) static void
test_evbuffer_find(void *ptr)
{
	u_char* p;
	const char* test1 = "1234567890\r\n";
	const char* test2 = "1234567890\r";
#define EVBUFFER_INITIAL_LENGTH 256
	char test3[EVBUFFER_INITIAL_LENGTH];
	unsigned int i;
	struct evbuffer * buf = evbuffer_new();

	tt_assert(buf);

	/* make sure evbuffer_find doesn't match past the end of the buffer */
	evbuffer_add(buf, (u_char*)test1, strlen(test1));
	evbuffer_validate(buf);
	evbuffer_drain(buf, strlen(test1));
	evbuffer_validate(buf);
	evbuffer_add(buf, (u_char*)test2, strlen(test2));
	evbuffer_validate(buf);
	p = evbuffer_find(buf, (u_char*)"\r\n", 2);
	tt_want(p == NULL);

	/*
	 * drain the buffer and do another find; in r309 this would
	 * read past the allocated buffer causing a valgrind error.
	 */
	evbuffer_drain(buf, strlen(test2));
	evbuffer_validate(buf);
	for (i = 0; i < EVBUFFER_INITIAL_LENGTH; ++i)
		test3[i] = 'a';
	test3[EVBUFFER_INITIAL_LENGTH - 1] = 'x';
	evbuffer_add(buf, (u_char *)test3, EVBUFFER_INITIAL_LENGTH);
	evbuffer_validate(buf);
	p = evbuffer_find(buf, (u_char *)"xy", 2);
	tt_want(p == NULL);

	/* simple test for match at end of allocated buffer */
	p = evbuffer_find(buf, (u_char *)"ax", 2);
	tt_assert(p != NULL);
	tt_want(strncmp((char*)p, "ax", 2) == 0);

end:
	if (buf)
		evbuffer_free(buf);
}