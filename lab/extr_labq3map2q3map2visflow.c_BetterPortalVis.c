#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ nummightsee; int /*<<< orphan*/  portalvis; int /*<<< orphan*/  portalflood; int /*<<< orphan*/  leaf; scalar_t__ removed; } ;
typedef  TYPE_1__ vportal_t ;

/* Variables and functions */
 scalar_t__ CountBits (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RecursiveLeafBitFlow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_vis ; 
 int numportals ; 
 TYPE_1__* portals ; 

void BetterPortalVis( int portalnum ){
	vportal_t   *p;

	p = portals + portalnum;

	if ( p->removed ) {
		return;
	}

	RecursiveLeafBitFlow( p->leaf, p->portalflood, p->portalvis );

	// build leaf vis information
	p->nummightsee = CountBits( p->portalvis, numportals * 2 );
	c_vis += p->nummightsee;
}