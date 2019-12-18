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
struct in_ifinfo {int /*<<< orphan*/  ii_llt; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IFADDR ; 
 int /*<<< orphan*/  free (struct in_ifinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igmp_domifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  lltable_free (int /*<<< orphan*/ ) ; 

void
in_domifdetach(struct ifnet *ifp, void *aux)
{
	struct in_ifinfo *ii = (struct in_ifinfo *)aux;

	igmp_domifdetach(ifp);
	lltable_free(ii->ii_llt);
	free(ii, M_IFADDR);
}