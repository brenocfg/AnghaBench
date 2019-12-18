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
struct evbuffer_chain {int flags; scalar_t__ misalign; size_t buffer_len; size_t off; scalar_t__ buffer; } ;
struct evbuffer {size_t total_len; size_t n_add_for_cb; struct evbuffer_chain* last; scalar_t__ freeze_end; } ;
typedef  scalar_t__ ev_uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHAIN_PINNED (struct evbuffer_chain*) ; 
 scalar_t__ EVBUFFER_CHAIN_MAX ; 
 int EVBUFFER_CHAIN_MAX_AUTO_SIZE ; 
 int EVBUFFER_IMMUTABLE ; 
 int /*<<< orphan*/  EVBUFFER_LOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  EVBUFFER_UNLOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 size_t EV_SIZE_MAX ; 
 int /*<<< orphan*/  evbuffer_chain_align (struct evbuffer_chain*) ; 
 int /*<<< orphan*/  evbuffer_chain_insert (struct evbuffer*,struct evbuffer_chain*) ; 
 struct evbuffer_chain* evbuffer_chain_new (size_t) ; 
 scalar_t__ evbuffer_chain_should_realign (struct evbuffer_chain*,size_t) ; 
 int /*<<< orphan*/  evbuffer_invoke_callbacks_ (struct evbuffer*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char const*,size_t) ; 

int
evbuffer_add(struct evbuffer *buf, const void *data_in, size_t datlen)
{
	struct evbuffer_chain *chain, *tmp;
	const unsigned char *data = data_in;
	size_t remain, to_alloc;
	int result = -1;

	EVBUFFER_LOCK(buf);

	if (buf->freeze_end) {
		goto done;
	}
	/* Prevent buf->total_len overflow */
	if (datlen > EV_SIZE_MAX - buf->total_len) {
		goto done;
	}

	chain = buf->last;

	/* If there are no chains allocated for this buffer, allocate one
	 * big enough to hold all the data. */
	if (chain == NULL) {
		chain = evbuffer_chain_new(datlen);
		if (!chain)
			goto done;
		evbuffer_chain_insert(buf, chain);
	}

	if ((chain->flags & EVBUFFER_IMMUTABLE) == 0) {
		/* Always true for mutable buffers */
		EVUTIL_ASSERT(chain->misalign >= 0 &&
		    (ev_uint64_t)chain->misalign <= EVBUFFER_CHAIN_MAX);
		remain = chain->buffer_len - (size_t)chain->misalign - chain->off;
		if (remain >= datlen) {
			/* there's enough space to hold all the data in the
			 * current last chain */
			memcpy(chain->buffer + chain->misalign + chain->off,
			    data, datlen);
			chain->off += datlen;
			buf->total_len += datlen;
			buf->n_add_for_cb += datlen;
			goto out;
		} else if (!CHAIN_PINNED(chain) &&
		    evbuffer_chain_should_realign(chain, datlen)) {
			/* we can fit the data into the misalignment */
			evbuffer_chain_align(chain);

			memcpy(chain->buffer + chain->off, data, datlen);
			chain->off += datlen;
			buf->total_len += datlen;
			buf->n_add_for_cb += datlen;
			goto out;
		}
	} else {
		/* we cannot write any data to the last chain */
		remain = 0;
	}

	/* we need to add another chain */
	to_alloc = chain->buffer_len;
	if (to_alloc <= EVBUFFER_CHAIN_MAX_AUTO_SIZE/2)
		to_alloc <<= 1;
	if (datlen > to_alloc)
		to_alloc = datlen;
	tmp = evbuffer_chain_new(to_alloc);
	if (tmp == NULL)
		goto done;

	if (remain) {
		memcpy(chain->buffer + chain->misalign + chain->off,
		    data, remain);
		chain->off += remain;
		buf->total_len += remain;
		buf->n_add_for_cb += remain;
	}

	data += remain;
	datlen -= remain;

	memcpy(tmp->buffer, data, datlen);
	tmp->off = datlen;
	evbuffer_chain_insert(buf, tmp);
	buf->n_add_for_cb += datlen;

out:
	evbuffer_invoke_callbacks_(buf);
	result = 0;
done:
	EVBUFFER_UNLOCK(buf);
	return result;
}