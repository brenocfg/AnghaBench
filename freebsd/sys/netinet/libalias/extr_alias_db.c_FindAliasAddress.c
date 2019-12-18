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
struct in_addr {scalar_t__ s_addr; } ;
struct libalias {struct in_addr aliasAddress; int /*<<< orphan*/  nullAddress; } ;
struct alias_link {struct in_addr alias_addr; } ;

/* Variables and functions */
 struct alias_link* FindLinkOut (struct libalias*,struct in_addr,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ INADDR_ANY ; 
 int /*<<< orphan*/  LIBALIAS_LOCK_ASSERT (struct libalias*) ; 
 int /*<<< orphan*/  LINK_ADDR ; 

struct in_addr
FindAliasAddress(struct libalias *la, struct in_addr original_addr)
{
	struct alias_link *lnk;

	LIBALIAS_LOCK_ASSERT(la);
	lnk = FindLinkOut(la, original_addr, la->nullAddress,
	    0, 0, LINK_ADDR, 0);
	if (lnk == NULL) {
		return (la->aliasAddress.s_addr != INADDR_ANY) ?
		    la->aliasAddress : original_addr;
	} else {
		if (lnk->alias_addr.s_addr == INADDR_ANY)
			return (la->aliasAddress.s_addr != INADDR_ANY) ?
			    la->aliasAddress : original_addr;
		else
			return (lnk->alias_addr);
	}
}