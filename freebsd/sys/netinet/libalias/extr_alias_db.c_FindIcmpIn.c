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
typedef  int /*<<< orphan*/  u_short ;
struct libalias {int packetAliasMode; } ;
struct in_addr {int dummy; } ;
struct alias_link {int dummy; } ;

/* Variables and functions */
 struct alias_link* AddLink (struct libalias*,struct in_addr,struct in_addr,struct in_addr,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct alias_link* FindLinkIn (struct libalias*,struct in_addr,struct in_addr,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct in_addr FindOriginalAddress (struct libalias*,struct in_addr) ; 
 int /*<<< orphan*/  LIBALIAS_LOCK_ASSERT (struct libalias*) ; 
 int /*<<< orphan*/  LINK_ICMP ; 
 int /*<<< orphan*/  NO_DEST_PORT ; 
 int PKT_ALIAS_DENY_INCOMING ; 

struct alias_link *
FindIcmpIn(struct libalias *la, struct in_addr dst_addr,
    struct in_addr alias_addr,
    u_short id_alias,
    int create)
{
	struct alias_link *lnk;

	LIBALIAS_LOCK_ASSERT(la);
	lnk = FindLinkIn(la, dst_addr, alias_addr,
	    NO_DEST_PORT, id_alias,
	    LINK_ICMP, 0);
	if (lnk == NULL && create && !(la->packetAliasMode & PKT_ALIAS_DENY_INCOMING)) {
		struct in_addr target_addr;

		target_addr = FindOriginalAddress(la, alias_addr);
		lnk = AddLink(la, target_addr, dst_addr, alias_addr,
		    id_alias, NO_DEST_PORT, id_alias,
		    LINK_ICMP);
	}
	return (lnk);
}