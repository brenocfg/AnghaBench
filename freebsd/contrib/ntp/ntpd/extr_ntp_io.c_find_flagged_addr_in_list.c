#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32 ;
typedef  int /*<<< orphan*/  sockaddr_u ;
struct TYPE_5__ {TYPE_2__* ep; int /*<<< orphan*/  addr; struct TYPE_5__* link; } ;
typedef  TYPE_1__ remaddr_t ;
struct TYPE_6__ {int flags; } ;
typedef  TYPE_2__ endpt ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 scalar_t__ SOCK_EQ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* remoteaddr_list ; 
 int /*<<< orphan*/  stoa (int /*<<< orphan*/ *) ; 

__attribute__((used)) static endpt *
find_flagged_addr_in_list(
	sockaddr_u *	addr,
	u_int32		flags
	)
{
	remaddr_t *entry;

	DPRINTF(4, ("Finding addr %s with flags %d in list: ",
		    stoa(addr), flags));

	for (entry = remoteaddr_list;
	     entry != NULL;
	     entry = entry->link)

		if (SOCK_EQ(&entry->addr, addr)
		    && (entry->ep->flags & flags) == flags) {

			DPRINTF(4, ("FOUND\n"));
			return entry->ep;
		}

	DPRINTF(4, ("NOT FOUND\n"));
	return NULL;
}