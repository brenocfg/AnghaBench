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
struct evbuffer_iovec {size_t iov_len; void* iov_base; } ;
struct evbuffer_chain {struct evbuffer_chain* next; } ;
struct evbuffer {struct evbuffer_chain** last_with_datap; } ;
typedef  size_t ev_ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EVBUFFER_LOCKED (struct evbuffer*) ; 
 scalar_t__ CHAIN_SPACE_LEN (struct evbuffer_chain*) ; 
 scalar_t__ CHAIN_SPACE_PTR (struct evbuffer_chain*) ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (struct evbuffer_chain*) ; 

int
evbuffer_read_setup_vecs_(struct evbuffer *buf, ev_ssize_t howmuch,
    struct evbuffer_iovec *vecs, int n_vecs_avail,
    struct evbuffer_chain ***chainp, int exact)
{
	struct evbuffer_chain *chain;
	struct evbuffer_chain **firstchainp;
	size_t so_far;
	int i;
	ASSERT_EVBUFFER_LOCKED(buf);

	if (howmuch < 0)
		return -1;

	so_far = 0;
	/* Let firstchain be the first chain with any space on it */
	firstchainp = buf->last_with_datap;
	EVUTIL_ASSERT(*firstchainp);
	if (CHAIN_SPACE_LEN(*firstchainp) == 0) {
		firstchainp = &(*firstchainp)->next;
	}

	chain = *firstchainp;
	EVUTIL_ASSERT(chain);
	for (i = 0; i < n_vecs_avail && so_far < (size_t)howmuch; ++i) {
		size_t avail = (size_t) CHAIN_SPACE_LEN(chain);
		if (avail > (howmuch - so_far) && exact)
			avail = howmuch - so_far;
		vecs[i].iov_base = (void *)CHAIN_SPACE_PTR(chain);
		vecs[i].iov_len = avail;
		so_far += avail;
		chain = chain->next;
	}

	*chainp = firstchainp;
	return i;
}