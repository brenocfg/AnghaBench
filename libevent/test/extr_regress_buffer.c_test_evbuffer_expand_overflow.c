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
 int /*<<< orphan*/  EVBUFFER_CHAIN_MAX ; 
 int /*<<< orphan*/  EV_SIZE_MAX ; 
 int /*<<< orphan*/  evbuffer_add (struct evbuffer*,char*,int) ; 
 int /*<<< orphan*/  evbuffer_expand (struct evbuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_free (struct evbuffer*) ; 
 struct evbuffer* evbuffer_new () ; 
 int /*<<< orphan*/  evbuffer_validate (struct evbuffer*) ; 

__attribute__((used)) static void
test_evbuffer_expand_overflow(void *ptr)
{
	struct evbuffer *buf;

	buf = evbuffer_new();
	evbuffer_add(buf, "1", 1);
	evbuffer_expand(buf, EVBUFFER_CHAIN_MAX);
	evbuffer_validate(buf);

	evbuffer_expand(buf, EV_SIZE_MAX);
	evbuffer_validate(buf);

end:
	evbuffer_free(buf);
}