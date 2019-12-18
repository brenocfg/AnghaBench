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
struct evbuffer_chain {scalar_t__ off; scalar_t__ buffer_len; scalar_t__ misalign; struct evbuffer_chain* next; } ;
struct evbuffer {struct evbuffer_chain* first; } ;

/* Variables and functions */

__attribute__((used)) static void
evbuffer_get_waste(struct evbuffer *buf, size_t *allocatedp, size_t *wastedp, size_t *usedp)
{
	struct evbuffer_chain *chain;
	size_t a, w, u;
	int n = 0;
	u = a = w = 0;

	chain = buf->first;
	/* skip empty at start */
	while (chain && chain->off==0) {
		++n;
		a += chain->buffer_len;
		chain = chain->next;
	}
	/* first nonempty chain: stuff at the end only is wasted. */
	if (chain) {
		++n;
		a += chain->buffer_len;
		u += chain->off;
		if (chain->next && chain->next->off)
			w += (size_t)(chain->buffer_len - (chain->misalign + chain->off));
		chain = chain->next;
	}
	/* subsequent nonempty chains */
	while (chain && chain->off) {
		++n;
		a += chain->buffer_len;
		w += (size_t)chain->misalign;
		u += chain->off;
		if (chain->next && chain->next->off)
			w += (size_t) (chain->buffer_len - (chain->misalign + chain->off));
		chain = chain->next;
	}
	/* subsequent empty chains */
	while (chain) {
		++n;
		a += chain->buffer_len;
	}
	*allocatedp = a;
	*wastedp = w;
	*usedp = u;
}