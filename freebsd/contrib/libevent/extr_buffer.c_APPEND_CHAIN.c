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
struct evbuffer_chain {int dummy; } ;
struct evbuffer {scalar_t__ total_len; int /*<<< orphan*/  last; struct evbuffer_chain** last_with_datap; struct evbuffer_chain* first; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EVBUFFER_LOCKED (struct evbuffer*) ; 
 struct evbuffer_chain** evbuffer_free_trailing_empty_chains (struct evbuffer*) ; 

__attribute__((used)) static void
APPEND_CHAIN(struct evbuffer *dst, struct evbuffer *src)
{
	struct evbuffer_chain **chp;

	ASSERT_EVBUFFER_LOCKED(dst);
	ASSERT_EVBUFFER_LOCKED(src);

	chp = evbuffer_free_trailing_empty_chains(dst);
	*chp = src->first;

	if (src->last_with_datap == &src->first)
		dst->last_with_datap = chp;
	else
		dst->last_with_datap = src->last_with_datap;
	dst->last = src->last;
	dst->total_len += src->total_len;
}