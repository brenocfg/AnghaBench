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
struct evbuffer {scalar_t__ off; int /*<<< orphan*/  buffer; int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* cb ) (struct evbuffer*,size_t,size_t,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SWAP (struct evbuffer*,struct evbuffer*) ; 
 int evbuffer_add (struct evbuffer*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  evbuffer_drain (struct evbuffer*,size_t) ; 
 int /*<<< orphan*/  stub1 (struct evbuffer*,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct evbuffer*,size_t,size_t,int /*<<< orphan*/ ) ; 

int
evbuffer_add_buffer(struct evbuffer *outbuf, struct evbuffer *inbuf)
{
	int res;

	/* Short cut for better performance */
	if (outbuf->off == 0) {
		struct evbuffer tmp;
		size_t oldoff = inbuf->off;

		/* Swap them directly */
		SWAP(&tmp, outbuf);
		SWAP(outbuf, inbuf);
		SWAP(inbuf, &tmp);

		/* 
		 * Optimization comes with a price; we need to notify the
		 * buffer if necessary of the changes. oldoff is the amount
		 * of data that we tranfered from inbuf to outbuf
		 */
		if (inbuf->off != oldoff && inbuf->cb != NULL)
			(*inbuf->cb)(inbuf, oldoff, inbuf->off, inbuf->cbarg);
		if (oldoff && outbuf->cb != NULL)
			(*outbuf->cb)(outbuf, 0, oldoff, outbuf->cbarg);
		
		return (0);
	}

	res = evbuffer_add(outbuf, inbuf->buffer, inbuf->off);
	if (res == 0) {
		/* We drain the input buffer on success */
		evbuffer_drain(inbuf, inbuf->off);
	}

	return (res);
}