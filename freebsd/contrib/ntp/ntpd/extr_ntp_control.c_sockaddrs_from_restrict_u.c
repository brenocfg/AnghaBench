#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_17__ {void* sa_family; } ;
struct TYPE_14__ {void* s_addr; } ;
struct TYPE_15__ {TYPE_1__ sin_addr; } ;
struct TYPE_21__ {TYPE_5__ sa6; TYPE_4__ sa; TYPE_2__ sa4; } ;
typedef  TYPE_8__ sockaddr_u ;
struct TYPE_19__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;
struct TYPE_16__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;
struct TYPE_20__ {TYPE_6__ v6; TYPE_3__ v4; } ;
struct TYPE_22__ {TYPE_7__ u; } ;
typedef  TYPE_9__ restrict_u ;

/* Variables and functions */
 void* AF_INET ; 
 void* AF_INET6 ; 
 int /*<<< orphan*/  ZERO (TYPE_8__) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
sockaddrs_from_restrict_u(
	sockaddr_u *	psaA,
	sockaddr_u *	psaM,
	restrict_u *	pres,
	int		ipv6
	)
{
	ZERO(*psaA);
	ZERO(*psaM);
	if (!ipv6) {
		psaA->sa.sa_family = AF_INET;
		psaA->sa4.sin_addr.s_addr = htonl(pres->u.v4.addr);
		psaM->sa.sa_family = AF_INET;
		psaM->sa4.sin_addr.s_addr = htonl(pres->u.v4.mask);
	} else {
		psaA->sa.sa_family = AF_INET6;
		memcpy(&psaA->sa6.sin6_addr, &pres->u.v6.addr,
		       sizeof(psaA->sa6.sin6_addr));
		psaM->sa.sa_family = AF_INET6;
		memcpy(&psaM->sa6.sin6_addr, &pres->u.v6.mask,
		       sizeof(psaA->sa6.sin6_addr));
	}
}