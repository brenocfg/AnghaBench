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
struct TYPE_2__ {int s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin6_addr; scalar_t__ sin6_family; TYPE_1__ sin_addr; scalar_t__ sin_family; } ;
struct sockaddr {int dummy; } ;
struct sa_in6 {int /*<<< orphan*/  sin6_addr; scalar_t__ sin6_family; TYPE_1__ sin_addr; scalar_t__ sin_family; } ;
struct in6_addr {int dummy; } ;
typedef  int in_addr_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  APPLY_MASK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_LEN (struct sockaddr_in) ; 
 int /*<<< orphan*/  KEY_LEN_INET ; 
 int /*<<< orphan*/  KEY_LEN_INET6 ; 
 int htonl (int) ; 
 int /*<<< orphan*/  ipv6_writemask (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static void
tei_to_sockaddr_ent(struct tentry_info *tei, struct sockaddr *sa,
    struct sockaddr *ma, int *set_mask)
{
	int mlen;
#ifdef INET
	struct sockaddr_in *addr, *mask;
#endif
#ifdef INET6
	struct sa_in6 *addr6, *mask6;
#endif
	in_addr_t a4;

	mlen = tei->masklen;

	if (tei->subtype == AF_INET) {
#ifdef INET
		addr = (struct sockaddr_in *)sa;
		mask = (struct sockaddr_in *)ma;
		/* Set 'total' structure length */
		KEY_LEN(*addr) = KEY_LEN_INET;
		KEY_LEN(*mask) = KEY_LEN_INET;
		addr->sin_family = AF_INET;
		mask->sin_addr.s_addr =
		    htonl(mlen ? ~((1 << (32 - mlen)) - 1) : 0);
		a4 = *((in_addr_t *)tei->paddr);
		addr->sin_addr.s_addr = a4 & mask->sin_addr.s_addr;
		if (mlen != 32)
			*set_mask = 1;
		else
			*set_mask = 0;
#endif
#ifdef INET6
	} else if (tei->subtype == AF_INET6) {
		/* IPv6 case */
		addr6 = (struct sa_in6 *)sa;
		mask6 = (struct sa_in6 *)ma;
		/* Set 'total' structure length */
		KEY_LEN(*addr6) = KEY_LEN_INET6;
		KEY_LEN(*mask6) = KEY_LEN_INET6;
		addr6->sin6_family = AF_INET6;
		ipv6_writemask(&mask6->sin6_addr, mlen);
		memcpy(&addr6->sin6_addr, tei->paddr, sizeof(struct in6_addr));
		APPLY_MASK(&addr6->sin6_addr, &mask6->sin6_addr);
		if (mlen != 128)
			*set_mask = 1;
		else
			*set_mask = 0;
#endif
	}
}