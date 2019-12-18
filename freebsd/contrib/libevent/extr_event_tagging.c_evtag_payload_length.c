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
 int decode_int_internal (int /*<<< orphan*/ *,struct evbuffer*,int) ; 
 int decode_tag_internal (int /*<<< orphan*/ *,struct evbuffer*,int /*<<< orphan*/ ) ; 

int
evtag_payload_length(struct evbuffer *evbuf, ev_uint32_t *plength)
{
	int res, len;

	len = decode_tag_internal(NULL, evbuf, 0 /* dodrain */);
	if (len == -1)
		return (-1);

	res = decode_int_internal(plength, evbuf, len);
	if (res == -1)
		return (-1);

	return (0);
}