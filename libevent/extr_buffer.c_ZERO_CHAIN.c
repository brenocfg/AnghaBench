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
struct evbuffer {scalar_t__ total_len; int /*<<< orphan*/ * first; int /*<<< orphan*/ ** last_with_datap; int /*<<< orphan*/ * last; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EVBUFFER_LOCKED (struct evbuffer*) ; 

__attribute__((used)) static inline void
ZERO_CHAIN(struct evbuffer *dst)
{
	ASSERT_EVBUFFER_LOCKED(dst);
	dst->first = NULL;
	dst->last = NULL;
	dst->last_with_datap = &(dst)->first;
	dst->total_len = 0;
}