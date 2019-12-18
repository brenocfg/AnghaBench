#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct in_addr {scalar_t__ s_addr; } ;
struct libalias {int newDefaultLink; struct in_addr aliasAddress; struct in_addr targetAddress; int /*<<< orphan*/  nullAddress; } ;
struct alias_link {struct in_addr src_addr; TYPE_1__* server; } ;
struct TYPE_2__ {struct TYPE_2__* next; struct in_addr addr; } ;

/* Variables and functions */
 struct alias_link* FindLinkIn (struct libalias*,int /*<<< orphan*/ ,struct in_addr,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ INADDR_ANY ; 
 scalar_t__ INADDR_NONE ; 
 int /*<<< orphan*/  LIBALIAS_LOCK_ASSERT (struct libalias*) ; 
 int /*<<< orphan*/  LINK_ADDR ; 

struct in_addr
FindOriginalAddress(struct libalias *la, struct in_addr alias_addr)
{
	struct alias_link *lnk;

	LIBALIAS_LOCK_ASSERT(la);
	lnk = FindLinkIn(la, la->nullAddress, alias_addr,
	    0, 0, LINK_ADDR, 0);
	if (lnk == NULL) {
		la->newDefaultLink = 1;
		if (la->targetAddress.s_addr == INADDR_ANY)
			return (alias_addr);
		else if (la->targetAddress.s_addr == INADDR_NONE)
			return (la->aliasAddress.s_addr != INADDR_ANY) ?
			    la->aliasAddress : alias_addr;
		else
			return (la->targetAddress);
	} else {
		if (lnk->server != NULL) {	/* LSNAT link */
			struct in_addr src_addr;

			src_addr = lnk->server->addr;
			lnk->server = lnk->server->next;
			return (src_addr);
		} else if (lnk->src_addr.s_addr == INADDR_ANY)
			return (la->aliasAddress.s_addr != INADDR_ANY) ?
			    la->aliasAddress : alias_addr;
		else
			return (lnk->src_addr);
	}
}