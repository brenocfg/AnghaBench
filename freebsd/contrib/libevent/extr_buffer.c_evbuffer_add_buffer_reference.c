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
struct evbuffer_chain {int flags; struct evbuffer_chain* next; } ;
struct evbuffer {size_t total_len; size_t n_add_for_cb; struct evbuffer_chain* first; scalar_t__ freeze_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPEND_CHAIN_MULTICAST (struct evbuffer*,struct evbuffer*) ; 
 int EVBUFFER_FILESEGMENT ; 
 int /*<<< orphan*/  EVBUFFER_LOCK2 (struct evbuffer*,struct evbuffer*) ; 
 int EVBUFFER_MULTICAST ; 
 int EVBUFFER_SENDFILE ; 
 int /*<<< orphan*/  EVBUFFER_UNLOCK2 (struct evbuffer*,struct evbuffer*) ; 
 int /*<<< orphan*/  evbuffer_free_all_chains (struct evbuffer_chain*) ; 
 int /*<<< orphan*/  evbuffer_invoke_callbacks_ (struct evbuffer*) ; 

int
evbuffer_add_buffer_reference(struct evbuffer *outbuf, struct evbuffer *inbuf)
{
	size_t in_total_len, out_total_len;
	struct evbuffer_chain *chain;
	int result = 0;

	EVBUFFER_LOCK2(inbuf, outbuf);
	in_total_len = inbuf->total_len;
	out_total_len = outbuf->total_len;
	chain = inbuf->first;

	if (in_total_len == 0)
		goto done;

	if (outbuf->freeze_end || outbuf == inbuf) {
		result = -1;
		goto done;
	}

	for (; chain; chain = chain->next) {
		if ((chain->flags & (EVBUFFER_FILESEGMENT|EVBUFFER_SENDFILE|EVBUFFER_MULTICAST)) != 0) {
			/* chain type can not be referenced */
			result = -1;
			goto done;
		}
	}

	if (out_total_len == 0) {
		/* There might be an empty chain at the start of outbuf; free
		 * it. */
		evbuffer_free_all_chains(outbuf->first);
	}
	APPEND_CHAIN_MULTICAST(outbuf, inbuf);

	outbuf->n_add_for_cb += in_total_len;
	evbuffer_invoke_callbacks_(outbuf);

done:
	EVBUFFER_UNLOCK2(inbuf, outbuf);
	return result;
}