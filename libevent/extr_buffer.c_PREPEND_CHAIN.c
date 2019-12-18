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
struct evbuffer {TYPE_1__* last; int /*<<< orphan*/ ** last_with_datap; int /*<<< orphan*/ * first; scalar_t__ total_len; } ;
struct TYPE_2__ {int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EVBUFFER_LOCKED (struct evbuffer*) ; 

__attribute__((used)) static void
PREPEND_CHAIN(struct evbuffer *dst, struct evbuffer *src)
{
	ASSERT_EVBUFFER_LOCKED(dst);
	ASSERT_EVBUFFER_LOCKED(src);
	src->last->next = dst->first;
	dst->first = src->first;
	dst->total_len += src->total_len;
	if (*dst->last_with_datap == NULL) {
		if (src->last_with_datap == &(src)->first)
			dst->last_with_datap = &dst->first;
		else
			dst->last_with_datap = src->last_with_datap;
	} else if (dst->last_with_datap == &dst->first) {
		dst->last_with_datap = &src->last->next;
	}
}