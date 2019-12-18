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
struct peer {int cast_flags; struct peer* p_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int MDF_TXONLY_MASK ; 
 int /*<<< orphan*/  current_time ; 
 int /*<<< orphan*/  peer_clear (struct peer*,char*) ; 
 struct peer* peer_list ; 

void
clear_all(void)
{
	struct peer *p;

	/*
	 * This routine is called when the clock is stepped, and so all
	 * previously saved time values are untrusted.
	 */
	for (p = peer_list; p != NULL; p = p->p_link)
		if (!(MDF_TXONLY_MASK & p->cast_flags))
			peer_clear(p, "STEP");

	DPRINTF(1, ("clear_all: at %lu\n", current_time));
}