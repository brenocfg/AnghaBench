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
typedef  int /*<<< orphan*/  u_short ;
struct in_addr {scalar_t__ s_addr; } ;
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct libalias {struct in_addr nullAddress; TYPE_1__ aliasAddress; } ;
struct alias_link {int dummy; } ;

/* Variables and functions */
 scalar_t__ INADDR_ANY ; 
 int /*<<< orphan*/  LIBALIAS_LOCK_ASSERT (struct libalias*) ; 
 struct alias_link* _FindLinkOut (struct libalias*,struct in_addr,struct in_addr,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static struct alias_link *
FindLinkOut(struct libalias *la, struct in_addr src_addr,
    struct in_addr dst_addr,
    u_short src_port,
    u_short dst_port,
    int link_type,
    int replace_partial_links)
{
	struct alias_link *lnk;

	LIBALIAS_LOCK_ASSERT(la);
	lnk = _FindLinkOut(la, src_addr, dst_addr, src_port, dst_port,
	    link_type, replace_partial_links);

	if (lnk == NULL) {
		/*
		 * The following allows permanent links to be specified as
		 * using the default source address (i.e. device interface
		 * address) without knowing in advance what that address
		 * is.
		 */
		if (la->aliasAddress.s_addr != INADDR_ANY &&
		    src_addr.s_addr == la->aliasAddress.s_addr) {
			lnk = _FindLinkOut(la, la->nullAddress, dst_addr, src_port, dst_port,
			    link_type, replace_partial_links);
		}
	}
	return (lnk);
}