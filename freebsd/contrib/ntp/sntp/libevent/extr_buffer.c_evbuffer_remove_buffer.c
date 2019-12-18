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
struct evbuffer_chain {size_t off; scalar_t__ misalign; scalar_t__ buffer; struct evbuffer_chain* next; } ;
struct evbuffer {size_t total_len; size_t n_add_for_cb; size_t n_del_for_cb; struct evbuffer_chain* first; struct evbuffer_chain* last; struct evbuffer_chain** last_with_datap; scalar_t__ freeze_start; scalar_t__ freeze_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_LOCK2 (struct evbuffer*,struct evbuffer*) ; 
 int /*<<< orphan*/  EVBUFFER_UNLOCK2 (struct evbuffer*,struct evbuffer*) ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int /*<<< orphan*/  advance_last_with_data (struct evbuffer*) ; 
 int /*<<< orphan*/  evbuffer_add (struct evbuffer*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  evbuffer_add_buffer (struct evbuffer*,struct evbuffer*) ; 
 struct evbuffer_chain** evbuffer_free_trailing_empty_chains (struct evbuffer*) ; 
 int /*<<< orphan*/  evbuffer_invoke_callbacks_ (struct evbuffer*) ; 

int
evbuffer_remove_buffer(struct evbuffer *src, struct evbuffer *dst,
    size_t datlen)
{
	/*XXX We should have an option to force this to be zero-copy.*/

	/*XXX can fail badly on sendfile case. */
	struct evbuffer_chain *chain, *previous;
	size_t nread = 0;
	int result;

	EVBUFFER_LOCK2(src, dst);

	chain = previous = src->first;

	if (datlen == 0 || dst == src) {
		result = 0;
		goto done;
	}

	if (dst->freeze_end || src->freeze_start) {
		result = -1;
		goto done;
	}

	/* short-cut if there is no more data buffered */
	if (datlen >= src->total_len) {
		datlen = src->total_len;
		evbuffer_add_buffer(dst, src);
		result = (int)datlen; /*XXXX should return ev_ssize_t*/
		goto done;
	}

	/* removes chains if possible */
	while (chain->off <= datlen) {
		/* We can't remove the last with data from src unless we
		 * remove all chains, in which case we would have done the if
		 * block above */
		EVUTIL_ASSERT(chain != *src->last_with_datap);
		nread += chain->off;
		datlen -= chain->off;
		previous = chain;
		if (src->last_with_datap == &chain->next)
			src->last_with_datap = &src->first;
		chain = chain->next;
	}

	if (nread) {
		/* we can remove the chain */
		struct evbuffer_chain **chp;
		chp = evbuffer_free_trailing_empty_chains(dst);

		if (dst->first == NULL) {
			dst->first = src->first;
		} else {
			*chp = src->first;
		}
		dst->last = previous;
		previous->next = NULL;
		src->first = chain;
		advance_last_with_data(dst);

		dst->total_len += nread;
		dst->n_add_for_cb += nread;
	}

	/* we know that there is more data in the src buffer than
	 * we want to read, so we manually drain the chain */
	evbuffer_add(dst, chain->buffer + chain->misalign, datlen);
	chain->misalign += datlen;
	chain->off -= datlen;
	nread += datlen;

	/* You might think we would want to increment dst->n_add_for_cb
	 * here too.  But evbuffer_add above already took care of that.
	 */
	src->total_len -= nread;
	src->n_del_for_cb += nread;

	if (nread) {
		evbuffer_invoke_callbacks_(dst);
		evbuffer_invoke_callbacks_(src);
	}
	result = (int)nread;/*XXXX should change return type */

done:
	EVBUFFER_UNLOCK2(src, dst);
	return result;
}