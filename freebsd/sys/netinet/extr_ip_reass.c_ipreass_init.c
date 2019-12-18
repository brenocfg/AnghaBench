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
struct ipq {int dummy; } ;
struct TYPE_2__ {scalar_t__ count; int /*<<< orphan*/  lock; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IPREASS_NHASH ; 
 int IP_MAXFRAGPACKETS ; 
 int /*<<< orphan*/  IP_MAXFRAGS ; 
 scalar_t__ IS_DEFAULT_VNET (int /*<<< orphan*/ ) ; 
 int MTX_DEF ; 
 int MTX_DUPOK ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 TYPE_1__* V_ipq ; 
 int /*<<< orphan*/  V_ipq_hashseed ; 
 int /*<<< orphan*/  V_ipq_zone ; 
 int /*<<< orphan*/  V_ipreass_maxbucketsize ; 
 int V_maxfragsperpacket ; 
 int /*<<< orphan*/  arc4random () ; 
 int /*<<< orphan*/  curvnet ; 
 int /*<<< orphan*/  imax (int,int) ; 
 int /*<<< orphan*/  ipreass_zone_change ; 
 int /*<<< orphan*/  maxfrags ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nmbclusters_change ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uma_zone_set_max (int /*<<< orphan*/ ,int) ; 

void
ipreass_init(void)
{
	int max;

	for (int i = 0; i < IPREASS_NHASH; i++) {
		TAILQ_INIT(&V_ipq[i].head);
		mtx_init(&V_ipq[i].lock, "IP reassembly", NULL,
		    MTX_DEF | MTX_DUPOK);
		V_ipq[i].count = 0;
	}
	V_ipq_hashseed = arc4random();
	V_maxfragsperpacket = 16;
	V_ipq_zone = uma_zcreate("ipq", sizeof(struct ipq), NULL, NULL, NULL,
	    NULL, UMA_ALIGN_PTR, 0);
	max = IP_MAXFRAGPACKETS;
	max = uma_zone_set_max(V_ipq_zone, max);
	V_ipreass_maxbucketsize = imax(max / (IPREASS_NHASH / 2), 1);

	if (IS_DEFAULT_VNET(curvnet)) {
		maxfrags = IP_MAXFRAGS;
		EVENTHANDLER_REGISTER(nmbclusters_change, ipreass_zone_change,
		    NULL, EVENTHANDLER_PRI_ANY);
	}
}