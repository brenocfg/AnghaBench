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
typedef  int /*<<< orphan*/  u_char ;
struct libalias {int dummy; } ;
struct in_addr {int dummy; } ;
struct alias_link {int dummy; } ;

/* Variables and functions */
 struct alias_link* AddLink (struct libalias*,struct in_addr,struct in_addr,struct in_addr,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct in_addr FindAliasAddress (struct libalias*,struct in_addr) ; 
 struct alias_link* FindLinkOut (struct libalias*,struct in_addr,struct in_addr,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LIBALIAS_LOCK_ASSERT (struct libalias*) ; 
 int /*<<< orphan*/  NO_DEST_PORT ; 
 int /*<<< orphan*/  NO_SRC_PORT ; 

struct alias_link *
FindProtoOut(struct libalias *la, struct in_addr src_addr,
    struct in_addr dst_addr,
    u_char proto)
{
	struct alias_link *lnk;

	LIBALIAS_LOCK_ASSERT(la);
	lnk = FindLinkOut(la, src_addr, dst_addr,
	    NO_SRC_PORT, NO_DEST_PORT,
	    proto, 1);

	if (lnk == NULL) {
		struct in_addr alias_addr;

		alias_addr = FindAliasAddress(la, src_addr);
		lnk = AddLink(la, src_addr, dst_addr, alias_addr,
		    NO_SRC_PORT, NO_DEST_PORT, 0,
		    proto);
	}
	return (lnk);
}