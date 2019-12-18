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
 int /*<<< orphan*/  evtag_marshal (struct evbuffer*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 

void
evtag_marshal_string(struct evbuffer *buf, ev_uint32_t tag, const char *string)
{
	/* TODO support strings longer than UINT32_MAX ? */
	evtag_marshal(buf, tag, string, (ev_uint32_t)strlen(string));
}