#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_len; TYPE_1__ sin_addr; void* sin_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_6__ {TYPE_2__ sin_addr; } ;
struct in_ifaddr {TYPE_3__ ia_addr; struct ifnet* ia_ifp; int /*<<< orphan*/  ia_subnetmask; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  mask ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 void* AF_INET ; 
 int /*<<< orphan*/  LLE_IFADDR ; 
 int /*<<< orphan*/  LLTABLE (struct ifnet*) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  lltable_delete_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*) ; 
 int /*<<< orphan*/  lltable_prefix_free (void*,struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
in_scrubprefixlle(struct in_ifaddr *ia, int all, u_int flags)
{
	struct sockaddr_in addr, mask;
	struct sockaddr *saddr, *smask;
	struct ifnet *ifp;

	saddr = (struct sockaddr *)&addr;
	bzero(&addr, sizeof(addr));
	addr.sin_len = sizeof(addr);
	addr.sin_family = AF_INET;
	smask = (struct sockaddr *)&mask;
	bzero(&mask, sizeof(mask));
	mask.sin_len = sizeof(mask);
	mask.sin_family = AF_INET;
	mask.sin_addr.s_addr = ia->ia_subnetmask;
	ifp = ia->ia_ifp;

	if (all) {

		/*
		 * Remove all L2 entries matching given prefix.
		 * Convert address to host representation to avoid
		 * doing this on every callback. ia_subnetmask is already
		 * stored in host representation.
		 */
		addr.sin_addr.s_addr = ntohl(ia->ia_addr.sin_addr.s_addr);
		lltable_prefix_free(AF_INET, saddr, smask, flags);
	} else {
		/* Remove interface address only */
		addr.sin_addr.s_addr = ia->ia_addr.sin_addr.s_addr;
		lltable_delete_addr(LLTABLE(ifp), LLE_IFADDR, saddr);
	}
}