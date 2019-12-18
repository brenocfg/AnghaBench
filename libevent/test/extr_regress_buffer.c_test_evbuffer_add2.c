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
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int EVBUFFER_CHAIN_SIZE ; 
 int MIN_BUFFER_SIZE ; 
 int /*<<< orphan*/  evbuffer_add (struct evbuffer*,char*,int) ; 
 int /*<<< orphan*/  evbuffer_add_printf (struct evbuffer*,char*) ; 
 int /*<<< orphan*/  evbuffer_expand (struct evbuffer*,int) ; 
 int /*<<< orphan*/  evbuffer_free (struct evbuffer*) ; 
 int evbuffer_get_length (struct evbuffer*) ; 
 struct evbuffer* evbuffer_new () ; 
 scalar_t__ evbuffer_pullup (struct evbuffer*,int) ; 
 int /*<<< orphan*/  evbuffer_validate (struct evbuffer*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
test_evbuffer_add2(void *ptr)
{
	struct evbuffer *buf;
	static char data[4096];
	int data_len = MIN_BUFFER_SIZE-EVBUFFER_CHAIN_SIZE-10;
	char *str;
	int len;

	memset(data, 'P', sizeof(data));
	buf = evbuffer_new();
	evbuffer_add(buf, data, data_len);
	evbuffer_validate(buf);
	evbuffer_expand(buf, 100);
	evbuffer_validate(buf);
	evbuffer_add(buf, "2", 1);
	evbuffer_validate(buf);
	evbuffer_add_printf(buf, "3");
	evbuffer_validate(buf);

	len = evbuffer_get_length(buf);
	tt_assert(len == data_len+2);
	str = (char *)evbuffer_pullup(buf, -1);
	tt_assert(str[len-3] == 'P');
	tt_assert(str[len-2] == '2');
	tt_assert(str[len-1] == '3');
end:
	evbuffer_free(buf);
}