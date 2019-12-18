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
struct tentry_info {int masklen; scalar_t__ subtype; scalar_t__ paddr; } ;
struct in6_addr {int dummy; } ;
struct TYPE_2__ {int a4; int /*<<< orphan*/  a6; } ;
struct chashentry {TYPE_1__ a; scalar_t__ type; } ;
typedef  int /*<<< orphan*/  in_addr_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  APPLY_MASK (int /*<<< orphan*/ *,struct in6_addr*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ipv6_writemask (struct in6_addr*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tei_to_chash_ent(struct tentry_info *tei, struct chashentry *ent)
{
	int mlen;
#ifdef INET6
	struct in6_addr mask6;
#endif


	mlen = tei->masklen;
	
	if (tei->subtype == AF_INET) {
#ifdef INET
		if (mlen > 32)
			return (EINVAL);
		ent->type = AF_INET;

		/* Calculate masked address */
		ent->a.a4 = ntohl(*((in_addr_t *)tei->paddr)) >> (32 - mlen);
#endif
#ifdef INET6
	} else if (tei->subtype == AF_INET6) {
		/* IPv6 case */
		if (mlen > 128)
			return (EINVAL);
		ent->type = AF_INET6;

		ipv6_writemask(&mask6, mlen);
		memcpy(&ent->a.a6, tei->paddr, sizeof(struct in6_addr));
		APPLY_MASK(&ent->a.a6, &mask6);
#endif
	} else {
		/* Unknown CIDR type */
		return (EINVAL);
	}

	return (0);
}