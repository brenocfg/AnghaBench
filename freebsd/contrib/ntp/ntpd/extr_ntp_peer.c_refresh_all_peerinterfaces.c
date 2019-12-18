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
struct peer {int reach; scalar_t__ dstadr; struct peer* p_link; } ;

/* Variables and functions */
 struct peer* peer_list ; 
 int /*<<< orphan*/  peer_refresh_interface (struct peer*) ; 

void
refresh_all_peerinterfaces(void)
{
	struct peer *p;

	/*
	 * this is called when the interface list has changed
	 * give all peers a chance to find a better interface
	 * but only if either they don't have an address already
	 * or if the one they have hasn't worked for a while.
	 */
	for (p = peer_list; p != NULL; p = p->p_link) {
		if (!(p->dstadr && (p->reach & 0x3)))	// Bug 2849 XOR 2043
			peer_refresh_interface(p);
	}
}