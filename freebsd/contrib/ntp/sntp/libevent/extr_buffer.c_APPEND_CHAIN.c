#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct evbuffer {scalar_t__ total_len; TYPE_1__* last; int /*<<< orphan*/ * last_with_datap; int /*<<< orphan*/  first; } ;
struct TYPE_2__ {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EVBUFFER_LOCKED (struct evbuffer*) ; 

__attribute__((used)) static void
APPEND_CHAIN(struct evbuffer *dst, struct evbuffer *src)
{
	ASSERT_EVBUFFER_LOCKED(dst);
	ASSERT_EVBUFFER_LOCKED(src);
	dst->last->next = src->first;
	if (src->last_with_datap == &src->first)
		dst->last_with_datap = &dst->last->next;
	else
		dst->last_with_datap = src->last_with_datap;
	dst->last = src->last;
	dst->total_len += src->total_len;
}