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
struct interface {int int_state; scalar_t__ int_addr; int /*<<< orphan*/  int_name; struct interface* int_nhash; } ;
typedef  scalar_t__ naddr ;

/* Variables and functions */
 scalar_t__ IF_RESCAN_DELAY () ; 
 int IS_ALIAS ; 
 int /*<<< orphan*/  ifinit () ; 
 struct interface** nhash (char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct interface *
ifwithname(char *name,			/* "ec0" or whatever */
	   naddr addr)			/* 0 or network address */
{
	struct interface *ifp;

	for (;;) {
		for (ifp = *nhash(name); ifp != NULL; ifp = ifp->int_nhash) {
			/* If the network address is not specified,
			 * ignore any alias interfaces.  Otherwise, look
			 * for the interface with the target name and address.
			 */
			if (!strcmp(ifp->int_name, name)
			    && ((addr == 0 && !(ifp->int_state & IS_ALIAS))
				|| (ifp->int_addr == addr)))
				return ifp;
		}

		/* If there is no known interface, maybe there is a
		 * new interface.  So just once look for new interfaces.
		 */
		if (IF_RESCAN_DELAY())
			return 0;
		ifinit();
	}
}