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
struct evbuffer {size_t off; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  evbuffer_drain (struct evbuffer*,size_t) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 

int
evbuffer_remove(struct evbuffer *buf, void *data, size_t datlen)
{
	size_t nread = datlen;
	if (nread >= buf->off)
		nread = buf->off;

	memcpy(data, buf->buffer, nread);
	evbuffer_drain(buf, nread);
	
	return (nread);
}