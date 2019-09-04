#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
struct TYPE_6__ {int leaf; int removed; int /*<<< orphan*/  winding; TYPE_2__ plane; } ;
typedef  TYPE_1__ vportal_t ;
typedef  TYPE_2__ visPlane_t ;
struct TYPE_8__ {int numportals; int merged; TYPE_1__** portals; } ;
typedef  TYPE_3__ leaf_t ;

/* Variables and functions */
 int MAX_PORTALS_ON_LEAF ; 
 scalar_t__ Winding_PlanesConcave (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* faceleafs ; 
 TYPE_3__* leafs ; 
 int qfalse ; 
 int qtrue ; 

int TryMergeLeaves( int l1num, int l2num ){
	int i, j, k, n, numportals;
	visPlane_t plane1, plane2;
	leaf_t *l1, *l2;
	vportal_t *p1, *p2;
	vportal_t *portals[MAX_PORTALS_ON_LEAF];

	for ( k = 0; k < 2; k++ )
	{
		if ( k ) {
			l1 = &leafs[l1num];
		}
		else{l1 = &faceleafs[l1num]; }
		for ( i = 0; i < l1->numportals; i++ )
		{
			p1 = l1->portals[i];
			if ( p1->leaf == l2num ) {
				continue;
			}
			for ( n = 0; n < 2; n++ )
			{
				if ( n ) {
					l2 = &leafs[l2num];
				}
				else{l2 = &faceleafs[l2num]; }
				for ( j = 0; j < l2->numportals; j++ )
				{
					p2 = l2->portals[j];
					if ( p2->leaf == l1num ) {
						continue;
					}
					//
					plane1 = p1->plane;
					plane2 = p2->plane;
					if ( Winding_PlanesConcave( p1->winding, p2->winding, plane1.normal, plane2.normal, plane1.dist, plane2.dist ) ) {
						return qfalse;
					}
				}
			}
		}
	}
	for ( k = 0; k < 2; k++ )
	{
		if ( k ) {
			l1 = &leafs[l1num];
			l2 = &leafs[l2num];
		}
		else
		{
			l1 = &faceleafs[l1num];
			l2 = &faceleafs[l2num];
		}
		numportals = 0;
		//the leaves can be merged now
		for ( i = 0; i < l1->numportals; i++ )
		{
			p1 = l1->portals[i];
			if ( p1->leaf == l2num ) {
				p1->removed = qtrue;
				continue;
			}
			portals[numportals++] = p1;
		}
		for ( j = 0; j < l2->numportals; j++ )
		{
			p2 = l2->portals[j];
			if ( p2->leaf == l1num ) {
				p2->removed = qtrue;
				continue;
			}
			portals[numportals++] = p2;
		}
		for ( i = 0; i < numportals; i++ )
		{
			l2->portals[i] = portals[i];
		}
		l2->numportals = numportals;
		l1->merged = l2num;
	}
	return qtrue;
}