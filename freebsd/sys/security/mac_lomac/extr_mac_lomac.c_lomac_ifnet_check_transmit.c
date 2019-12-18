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
struct mac_lomac {int dummy; } ;
struct label {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 struct mac_lomac* SLOT (struct label*) ; 
 int /*<<< orphan*/  lomac_enabled ; 
 scalar_t__ lomac_single_in_range (struct mac_lomac*,struct mac_lomac*) ; 

__attribute__((used)) static int
lomac_ifnet_check_transmit(struct ifnet *ifp, struct label *ifplabel,
    struct mbuf *m, struct label *mlabel)
{
	struct mac_lomac *p, *i;

	if (!lomac_enabled)
		return (0);

	p = SLOT(mlabel);
	i = SLOT(ifplabel);

	return (lomac_single_in_range(p, i) ? 0 : EACCES);
}