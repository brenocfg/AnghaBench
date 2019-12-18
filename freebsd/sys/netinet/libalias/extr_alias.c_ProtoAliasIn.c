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
typedef  int /*<<< orphan*/  u_char ;
struct libalias {int packetAliasMode; } ;
struct in_addr {int dummy; } ;
struct alias_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DifferentialChecksum (int /*<<< orphan*/ *,struct in_addr*,struct in_addr*,int) ; 
 struct alias_link* FindProtoIn (struct libalias*,struct in_addr,struct in_addr,int /*<<< orphan*/ ) ; 
 struct in_addr GetOriginalAddress (struct alias_link*) ; 
 int /*<<< orphan*/  LIBALIAS_LOCK_ASSERT (struct libalias*) ; 
 int PKT_ALIAS_IGNORED ; 
 int PKT_ALIAS_OK ; 
 int PKT_ALIAS_PROXY_ONLY ; 

__attribute__((used)) static int
ProtoAliasIn(struct libalias *la, struct in_addr ip_src, 
    struct in_addr *ip_dst, u_char ip_p, u_short *ip_sum)
{
/*
  Handle incoming IP packets. The
  only thing which is done in this case is to alias
  the dest IP address of the packet to our inside
  machine.
*/
	struct alias_link *lnk;

	LIBALIAS_LOCK_ASSERT(la);
/* Return if proxy-only mode is enabled */
	if (la->packetAliasMode & PKT_ALIAS_PROXY_ONLY)
		return (PKT_ALIAS_OK);

	lnk = FindProtoIn(la, ip_src, *ip_dst, ip_p);
	if (lnk != NULL) {
		struct in_addr original_address;

		original_address = GetOriginalAddress(lnk);

/* Restore original IP address */
		DifferentialChecksum(ip_sum,
		    &original_address, ip_dst, 2);
		*ip_dst = original_address;

		return (PKT_ALIAS_OK);
	}
	return (PKT_ALIAS_IGNORED);
}