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
struct evhttp {int flags; } ;

/* Variables and functions */
 int EVHTTP_SERVER_LINGERING_CLOSE ; 

int evhttp_set_flags(struct evhttp *http, int flags)
{
	int avail_flags = 0;
	avail_flags |= EVHTTP_SERVER_LINGERING_CLOSE;

	if (flags & ~avail_flags)
		return 1;
	http->flags &= ~avail_flags;

	http->flags |= flags;

	return 0;
}