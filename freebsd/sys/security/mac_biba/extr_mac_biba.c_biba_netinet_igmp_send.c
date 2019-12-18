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
struct mbuf {int dummy; } ;
struct mac_biba {int dummy; } ;
struct label {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_BIBA_TYPE_EQUAL ; 
 struct mac_biba* SLOT (struct label*) ; 
 int /*<<< orphan*/  biba_set_effective (struct mac_biba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
biba_netinet_igmp_send(struct ifnet *ifp, struct label *ifplabel,
    struct mbuf *m, struct label *mlabel)
{
	struct mac_biba *dest;

	dest = SLOT(mlabel);

	biba_set_effective(dest, MAC_BIBA_TYPE_EQUAL, 0, NULL);
}