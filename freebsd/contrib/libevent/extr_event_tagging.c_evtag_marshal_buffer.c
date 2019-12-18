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
 int /*<<< orphan*/  evbuffer_add_buffer (struct evbuffer*,struct evbuffer*) ; 
 scalar_t__ evbuffer_get_length (struct evbuffer*) ; 
 int /*<<< orphan*/  evtag_encode_int (struct evbuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evtag_encode_tag (struct evbuffer*,int /*<<< orphan*/ ) ; 

void
evtag_marshal_buffer(struct evbuffer *evbuf, ev_uint32_t tag,
    struct evbuffer *data)
{
	evtag_encode_tag(evbuf, tag);
	/* XXX support more than UINT32_MAX data */
	evtag_encode_int(evbuf, (ev_uint32_t)evbuffer_get_length(data));
	evbuffer_add_buffer(evbuf, data);
}