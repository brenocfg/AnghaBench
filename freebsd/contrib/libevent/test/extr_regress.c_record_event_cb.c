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
typedef  scalar_t__ evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  TT_BLATHER (char*) ; 
 int /*<<< orphan*/  have_closed ; 
 int premature_event ; 

__attribute__((used)) static void
record_event_cb(evutil_socket_t s, short what, void *ptr)
{
	short *whatp = ptr;
	if (!have_closed)
		premature_event = 1;
	*whatp = what;
	TT_BLATHER(("Recorded %d on socket %d", (int)what, (int)s));
}