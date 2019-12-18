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
 int evbuffer_add (struct evbuffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  evbuffer_drain (struct evbuffer*,int) ; 
 int /*<<< orphan*/  evbuffer_pullup (struct evbuffer*,int) ; 
 int evtag_unmarshal_header (struct evbuffer*,int /*<<< orphan*/ *) ; 

int
evtag_unmarshal(struct evbuffer *src, ev_uint32_t *ptag, struct evbuffer *dst)
{
	int len;

	if ((len = evtag_unmarshal_header(src, ptag)) == -1)
		return (-1);

	if (evbuffer_add(dst, evbuffer_pullup(src, len), len) == -1)
		return (-1);

	evbuffer_drain(src, len);

	return (len);
}