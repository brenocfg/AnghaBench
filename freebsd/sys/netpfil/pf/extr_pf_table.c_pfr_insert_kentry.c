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
struct pfr_ktable {int /*<<< orphan*/  pfrkt_cnt; } ;
struct TYPE_2__ {long pfrkc_tzero; } ;
struct pfr_kentry {TYPE_1__ pfrke_counters; } ;
struct pfr_addr {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct pfr_kentry* pfr_create_kentry (struct pfr_addr*) ; 
 struct pfr_kentry* pfr_lookup_addr (struct pfr_ktable*,struct pfr_addr*,int) ; 
 int pfr_route_kentry (struct pfr_ktable*,struct pfr_kentry*) ; 

int
pfr_insert_kentry(struct pfr_ktable *kt, struct pfr_addr *ad, long tzero)
{
	struct pfr_kentry	*p;
	int			 rv;

	p = pfr_lookup_addr(kt, ad, 1);
	if (p != NULL)
		return (0);
	p = pfr_create_kentry(ad);
	if (p == NULL)
		return (ENOMEM);

	rv = pfr_route_kentry(kt, p);
	if (rv)
		return (rv);

	p->pfrke_counters.pfrkc_tzero = tzero;
	kt->pfrkt_cnt++;

	return (0);
}