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
struct evbuffer {scalar_t__ total_len; struct evbuffer_chain* first; struct evbuffer_chain** last_with_datap; struct evbuffer_chain* last; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EVBUFFER_LOCKED (struct evbuffer*) ; 
 int /*<<< orphan*/  ZERO_CHAIN (struct evbuffer*) ; 

__attribute__((used)) static inline void
RESTORE_PINNED(struct evbuffer *src, struct evbuffer_chain *pinned,
		struct evbuffer_chain *last)
{
	ASSERT_EVBUFFER_LOCKED(src);

	if (!pinned) {
		ZERO_CHAIN(src);
		return;
	}

	src->first = pinned;
	src->last = last;
	src->last_with_datap = &src->first;
	src->total_len = 0;
}