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
struct evbuffer {TYPE_1__** last_with_datap; } ;
struct TYPE_2__ {struct TYPE_2__* next; scalar_t__ off; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EVBUFFER_LOCKED (struct evbuffer*) ; 

__attribute__((used)) static int
advance_last_with_data(struct evbuffer *buf)
{
	int n = 0;
	ASSERT_EVBUFFER_LOCKED(buf);

	if (!*buf->last_with_datap)
		return 0;

	while ((*buf->last_with_datap)->next && (*buf->last_with_datap)->next->off) {
		buf->last_with_datap = &(*buf->last_with_datap)->next;
		++n;
	}
	return n;
}