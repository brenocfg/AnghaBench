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
struct evbuffer {size_t off; size_t buffer; size_t orig_buffer; int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* cb ) (struct evbuffer*,size_t,size_t,int /*<<< orphan*/ ) ;scalar_t__ misalign; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct evbuffer*,size_t,size_t,int /*<<< orphan*/ ) ; 

void
evbuffer_drain(struct evbuffer *buf, size_t len)
{
	size_t oldoff = buf->off;

	if (len >= buf->off) {
		buf->off = 0;
		buf->buffer = buf->orig_buffer;
		buf->misalign = 0;
		goto done;
	}

	buf->buffer += len;
	buf->misalign += len;

	buf->off -= len;

 done:
	/* Tell someone about changes in this buffer */
	if (buf->off != oldoff && buf->cb != NULL)
		(*buf->cb)(buf, oldoff, buf->off, buf->cbarg);

}