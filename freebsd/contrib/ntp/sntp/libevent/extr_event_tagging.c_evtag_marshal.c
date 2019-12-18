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
struct evbuffer {int dummy; } ;
typedef  int /*<<< orphan*/  ev_uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  evbuffer_add (struct evbuffer*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evtag_encode_int (struct evbuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evtag_encode_tag (struct evbuffer*,int /*<<< orphan*/ ) ; 

void
evtag_marshal(struct evbuffer *evbuf, ev_uint32_t tag,
    const void *data, ev_uint32_t len)
{
	evtag_encode_tag(evbuf, tag);
	evtag_encode_int(evbuf, len);
	evbuffer_add(evbuf, (void *)data, len);
}