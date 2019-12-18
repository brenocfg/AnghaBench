#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct in6_addr {int dummy; } ;
struct TYPE_10__ {scalar_t__ kidx; } ;
struct TYPE_7__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  addr6; TYPE_1__ addr; } ;
struct TYPE_11__ {int masklen; TYPE_4__ v; scalar_t__ subtype; TYPE_3__ k; } ;
typedef  TYPE_5__ ipfw_obj_tentry ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int contigmask (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ta_dump_kfib_tentry_int(struct sockaddr *paddr, struct sockaddr *pmask,
    ipfw_obj_tentry *tent)
{
#ifdef INET
	struct sockaddr_in *addr, *mask;
#endif
#ifdef INET6
	struct sockaddr_in6 *addr6, *mask6;
#endif
	int len;

	len = 0;

	/* Guess IPv4/IPv6 radix by sockaddr family */
#ifdef INET
	if (paddr->sa_family == AF_INET) {
		addr = (struct sockaddr_in *)paddr;
		mask = (struct sockaddr_in *)pmask;
		tent->k.addr.s_addr = addr->sin_addr.s_addr;
		len = 32;
		if (mask != NULL)
			len = contigmask((uint8_t *)&mask->sin_addr, 32);
		if (len == -1)
			len = 0;
		tent->masklen = len;
		tent->subtype = AF_INET;
		tent->v.kidx = 0; /* Do we need to put GW here? */
	}
#endif
#ifdef INET6
	if (paddr->sa_family == AF_INET6) {
		addr6 = (struct sockaddr_in6 *)paddr;
		mask6 = (struct sockaddr_in6 *)pmask;
		memcpy(&tent->k.addr6, &addr6->sin6_addr,
		    sizeof(struct in6_addr));
		len = 128;
		if (mask6 != NULL)
			len = contigmask((uint8_t *)&mask6->sin6_addr, 128);
		if (len == -1)
			len = 0;
		tent->masklen = len;
		tent->subtype = AF_INET6;
		tent->v.kidx = 0;
	}
#endif

	return (0);
}