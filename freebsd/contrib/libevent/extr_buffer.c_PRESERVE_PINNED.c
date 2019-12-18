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
struct evbuffer_chain {scalar_t__ off; scalar_t__ misalign; scalar_t__ buffer; struct evbuffer_chain* next; } ;
struct evbuffer {struct evbuffer_chain** last_with_datap; struct evbuffer_chain* last; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EVBUFFER_LOCKED (struct evbuffer*) ; 
 int CHAIN_PINNED_R (struct evbuffer_chain*) ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int /*<<< orphan*/  HAS_PINNED_R (struct evbuffer*) ; 
 struct evbuffer_chain* evbuffer_chain_new (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
PRESERVE_PINNED(struct evbuffer *src, struct evbuffer_chain **first,
		struct evbuffer_chain **last)
{
	struct evbuffer_chain *chain, **pinned;

	ASSERT_EVBUFFER_LOCKED(src);

	if (!HAS_PINNED_R(src)) {
		*first = *last = NULL;
		return 0;
	}

	pinned = src->last_with_datap;
	if (!CHAIN_PINNED_R(*pinned))
		pinned = &(*pinned)->next;
	EVUTIL_ASSERT(CHAIN_PINNED_R(*pinned));
	chain = *first = *pinned;
	*last = src->last;

	/* If there's data in the first pinned chain, we need to allocate
	 * a new chain and copy the data over. */
	if (chain->off) {
		struct evbuffer_chain *tmp;

		EVUTIL_ASSERT(pinned == src->last_with_datap);
		tmp = evbuffer_chain_new(chain->off);
		if (!tmp)
			return -1;
		memcpy(tmp->buffer, chain->buffer + chain->misalign,
			chain->off);
		tmp->off = chain->off;
		*src->last_with_datap = tmp;
		src->last = tmp;
		chain->misalign += chain->off;
		chain->off = 0;
	} else {
		src->last = *src->last_with_datap;
		*pinned = NULL;
	}

	return 0;
}