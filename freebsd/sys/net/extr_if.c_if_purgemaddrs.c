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
struct ifnet {int /*<<< orphan*/  if_multiaddrs; } ;
struct ifmultiaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct ifmultiaddr* CK_STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CK_STAILQ_REMOVE (int /*<<< orphan*/ *,struct ifmultiaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IF_ADDR_WLOCK (struct ifnet*) ; 
 int /*<<< orphan*/  IF_ADDR_WUNLOCK (struct ifnet*) ; 
 int /*<<< orphan*/  if_delmulti_locked (struct ifnet*,struct ifmultiaddr*,int) ; 
 int /*<<< orphan*/  ifma_link ; 
 int /*<<< orphan*/  ifmultiaddr ; 

__attribute__((used)) static void
if_purgemaddrs(struct ifnet *ifp)
{
	struct ifmultiaddr *ifma;

	IF_ADDR_WLOCK(ifp);
	while (!CK_STAILQ_EMPTY(&ifp->if_multiaddrs)) {
		ifma = CK_STAILQ_FIRST(&ifp->if_multiaddrs);
		CK_STAILQ_REMOVE(&ifp->if_multiaddrs, ifma, ifmultiaddr, ifma_link);
		if_delmulti_locked(ifp, ifma, 1);
	}
	IF_ADDR_WUNLOCK(ifp);
}