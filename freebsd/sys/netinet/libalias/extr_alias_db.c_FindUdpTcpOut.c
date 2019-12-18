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
typedef  int u_char ;
struct libalias {int dummy; } ;
struct in_addr {int dummy; } ;
struct alias_link {int dummy; } ;

/* Variables and functions */
 struct alias_link* AddLink (struct libalias*,struct in_addr,struct in_addr,struct in_addr,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct in_addr FindAliasAddress (struct libalias*,struct in_addr) ; 
 struct alias_link* FindLinkOut (struct libalias*,struct in_addr,struct in_addr,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GET_ALIAS_PORT ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  LIBALIAS_LOCK_ASSERT (struct libalias*) ; 
 int LINK_TCP ; 
 int LINK_UDP ; 

struct alias_link *
FindUdpTcpOut(struct libalias *la, struct in_addr src_addr,
    struct in_addr dst_addr,
    u_short src_port,
    u_short dst_port,
    u_char proto,
    int create)
{
	int link_type;
	struct alias_link *lnk;

	LIBALIAS_LOCK_ASSERT(la);
	switch (proto) {
	case IPPROTO_UDP:
		link_type = LINK_UDP;
		break;
	case IPPROTO_TCP:
		link_type = LINK_TCP;
		break;
	default:
		return (NULL);
		break;
	}

	lnk = FindLinkOut(la, src_addr, dst_addr, src_port, dst_port, link_type, create);

	if (lnk == NULL && create) {
		struct in_addr alias_addr;

		alias_addr = FindAliasAddress(la, src_addr);
		lnk = AddLink(la, src_addr, dst_addr, alias_addr,
		    src_port, dst_port, GET_ALIAS_PORT,
		    link_type);
	}
	return (lnk);
}