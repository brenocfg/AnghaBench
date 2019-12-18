#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_2__ winding_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_7__ {scalar_t__* mins; scalar_t__* maxs; int numsides; TYPE_1__* sides; } ;
typedef  TYPE_3__ brush_t ;
struct TYPE_5__ {TYPE_2__* winding; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddPointToBounds (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  ClearBounds (scalar_t__*,scalar_t__*) ; 
 scalar_t__ MAX_WORLD_COORD ; 
 scalar_t__ MIN_WORLD_COORD ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean BoundBrush( brush_t *brush ){
	int i, j;
	winding_t   *w;


	ClearBounds( brush->mins, brush->maxs );
	for ( i = 0; i < brush->numsides; i++ )
	{
		w = brush->sides[ i ].winding;
		if ( w == NULL ) {
			continue;
		}
		for ( j = 0; j < w->numpoints; j++ )
			AddPointToBounds( w->p[ j ], brush->mins, brush->maxs );
	}

	for ( i = 0; i < 3; i++ )
	{
		if ( brush->mins[ i ] < MIN_WORLD_COORD || brush->maxs[ i ] > MAX_WORLD_COORD || brush->mins[i] >= brush->maxs[ i ] ) {
			return qfalse;
		}
	}

	return qtrue;
}