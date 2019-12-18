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
struct libalias {int /*<<< orphan*/  nullAddress; } ;
struct in_addr {int dummy; } ;
struct alias_link {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 struct alias_link* AddLink (struct libalias*,struct in_addr,int /*<<< orphan*/ ,struct in_addr,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIBALIAS_LOCK (struct libalias*) ; 
 int /*<<< orphan*/  LIBALIAS_UNLOCK (struct libalias*) ; 
 int /*<<< orphan*/  LINK_ADDR ; 
 int /*<<< orphan*/  LINK_PERMANENT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

struct alias_link *
LibAliasRedirectAddr(struct libalias *la, struct in_addr src_addr,
    struct in_addr alias_addr)
{
	struct alias_link *lnk;

	LIBALIAS_LOCK(la);
	lnk = AddLink(la, src_addr, la->nullAddress, alias_addr,
	    0, 0, 0,
	    LINK_ADDR);

	if (lnk != NULL) {
		lnk->flags |= LINK_PERMANENT;
	}
#ifdef LIBALIAS_DEBUG
	else {
		fprintf(stderr, "PacketAliasRedirectAddr(): "
		    "call to AddLink() failed\n");
	}
#endif

	LIBALIAS_UNLOCK(la);
	return (lnk);
}