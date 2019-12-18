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
typedef  scalar_t__ ev_uint32_t ;

/* Variables and functions */
 int decode_int_internal (scalar_t__*,struct evbuffer*,int /*<<< orphan*/ ) ; 
 int decode_tag_internal (scalar_t__*,struct evbuffer*,int) ; 
 int /*<<< orphan*/  evbuffer_drain (struct evbuffer*,scalar_t__) ; 
 scalar_t__ evbuffer_get_length (struct evbuffer*) ; 
 int evtag_decode_int (scalar_t__*,struct evbuffer*) ; 

int
evtag_unmarshal_int(struct evbuffer *evbuf, ev_uint32_t need_tag,
    ev_uint32_t *pinteger)
{
	ev_uint32_t tag;
	ev_uint32_t len;
	int result;

	if (decode_tag_internal(&tag, evbuf, 1 /* dodrain */) == -1)
		return (-1);
	if (need_tag != tag)
		return (-1);
	if (evtag_decode_int(&len, evbuf) == -1)
		return (-1);

	if (evbuffer_get_length(evbuf) < len)
		return (-1);

	result = decode_int_internal(pinteger, evbuf, 0);
	evbuffer_drain(evbuf, len);
	if (result < 0 || (size_t)result > len) /* XXX Should this be != rather than > ?*/
		return (-1);
	else
		return result;
}