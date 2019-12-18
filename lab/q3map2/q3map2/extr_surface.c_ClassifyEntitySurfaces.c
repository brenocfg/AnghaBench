#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int firstDrawSurf; } ;
typedef  TYPE_1__ entity_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClassifySurfaces (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FinishSurface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TidyEntitySurfaces (TYPE_1__*) ; 
 int /*<<< orphan*/ * mapDrawSurfs ; 
 int numMapDrawSurfs ; 

void ClassifyEntitySurfaces( entity_t *e ){
	int i;


	/* note it */
	Sys_FPrintf( SYS_VRB, "--- ClassifyEntitySurfaces ---\n" );

	/* walk the surface list */
	for ( i = e->firstDrawSurf; i < numMapDrawSurfs; i++ )
	{
		FinishSurface( &mapDrawSurfs[ i ] );
		ClassifySurfaces( 1, &mapDrawSurfs[ i ] );
	}

	/* tidy things up */
	TidyEntitySurfaces( e );
}