#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ winding_t ;
struct TYPE_7__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_2__ winding_accu_t ;

/* Variables and functions */
 TYPE_1__* AllocWinding (int) ; 
 int /*<<< orphan*/  Error (char*) ; 
 int /*<<< orphan*/  VectorCopyAccuToRegular (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

winding_t   *CopyWindingAccuToRegular( winding_accu_t *w ){
	int i;
	winding_t   *c;

	if ( !w ) {
		Error( "CopyWindingAccuToRegular: winding is NULL" );
	}

	c = AllocWinding( w->numpoints );
	c->numpoints = w->numpoints;
	for ( i = 0; i < c->numpoints; i++ )
	{
		VectorCopyAccuToRegular( w->p[i], c->p[i] );
	}
	return c;
}