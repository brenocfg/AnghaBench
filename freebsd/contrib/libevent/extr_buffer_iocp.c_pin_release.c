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
struct evbuffer_overlapped {int n_buffers; struct evbuffer_chain* first_pinned; } ;
struct evbuffer_chain {struct evbuffer_chain* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVUTIL_ASSERT (struct evbuffer_chain*) ; 
 int /*<<< orphan*/  evbuffer_chain_unpin_ (struct evbuffer_chain*,unsigned int) ; 

__attribute__((used)) static void
pin_release(struct evbuffer_overlapped *eo, unsigned flag)
{
	int i;
	struct evbuffer_chain *next, *chain = eo->first_pinned;

	for (i = 0; i < eo->n_buffers; ++i) {
		EVUTIL_ASSERT(chain);
		next = chain->next;
		evbuffer_chain_unpin_(chain, flag);
		chain = next;
	}
}