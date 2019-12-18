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
struct evbuffer {size_t off; size_t totallen; size_t buffer; int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* cb ) (struct evbuffer*,size_t,size_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  misalign; } ;

/* Variables and functions */
 int evbuffer_expand (struct evbuffer*,size_t) ; 
 int /*<<< orphan*/  memcpy (size_t,void const*,size_t) ; 
 int /*<<< orphan*/  stub1 (struct evbuffer*,size_t,size_t,int /*<<< orphan*/ ) ; 

int
evbuffer_add(struct evbuffer *buf, const void *data, size_t datlen)
{
	size_t need = buf->misalign + buf->off + datlen;
	size_t oldoff = buf->off;

	if (buf->totallen < need) {
		if (evbuffer_expand(buf, datlen) == -1)
			return (-1);
	}

	memcpy(buf->buffer + buf->off, data, datlen);
	buf->off += datlen;

	if (datlen && buf->cb != NULL)
		(*buf->cb)(buf, oldoff, buf->off, buf->cbarg);

	return (0);
}