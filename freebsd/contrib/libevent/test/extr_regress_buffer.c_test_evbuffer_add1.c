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
 int /*<<< orphan*/  evbuffer_add_printf (struct evbuffer*,char*) ; 
 int /*<<< orphan*/  evbuffer_expand (struct evbuffer*,int) ; 
 int /*<<< orphan*/  evbuffer_free (struct evbuffer*) ; 
 int evbuffer_get_length (struct evbuffer*) ; 
 struct evbuffer* evbuffer_new () ; 
 scalar_t__ evbuffer_pullup (struct evbuffer*,int) ; 
 int /*<<< orphan*/  evbuffer_validate (struct evbuffer*) ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
test_evbuffer_add1(void *ptr)
{
	struct evbuffer *buf;
	char *str;

	buf = evbuffer_new();
	evbuffer_add(buf, "1", 1);
	evbuffer_validate(buf);
	evbuffer_expand(buf, 2048);
	evbuffer_validate(buf);
	evbuffer_add(buf, "2", 1);
	evbuffer_validate(buf);
	evbuffer_add_printf(buf, "3");
	evbuffer_validate(buf);

	tt_assert(evbuffer_get_length(buf) == 3);
	str = (char *)evbuffer_pullup(buf, -1);
	tt_assert(str[0] == '1');
	tt_assert(str[1] == '2');
	tt_assert(str[2] == '3');
end:
	evbuffer_free(buf);
}