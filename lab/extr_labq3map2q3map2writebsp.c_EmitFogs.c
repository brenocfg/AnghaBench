#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int brushNum; int visibleSide; int /*<<< orphan*/  shader; } ;
struct TYPE_9__ {int visibleSide; TYPE_3__* brush; TYPE_1__* si; } ;
struct TYPE_8__ {int outputNum; TYPE_2__* sides; } ;
struct TYPE_7__ {int /*<<< orphan*/ * visibleHull; } ;
struct TYPE_6__ {int /*<<< orphan*/  shader; } ;

/* Variables and functions */
 int /*<<< orphan*/  Sys_Printf (char*,int,int) ; 
 TYPE_5__* bspFogs ; 
 TYPE_4__* mapFogs ; 
 int numBSPFogs ; 
 int numMapFogs ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void EmitFogs( void ){
	int i, j;


	/* setup */
	numBSPFogs = numMapFogs;

	/* walk list */
	for ( i = 0; i < numMapFogs; i++ )
	{
		/* set shader */
		strcpy( bspFogs[ i ].shader, mapFogs[ i ].si->shader );

		/* global fog doesn't have an associated brush */
		if ( mapFogs[ i ].brush == NULL ) {
			bspFogs[ i ].brushNum = -1;
			bspFogs[ i ].visibleSide = -1;
		}
		else
		{
			/* set brush */
			bspFogs[ i ].brushNum = mapFogs[ i ].brush->outputNum;

			/* try to use forced visible side */
			if ( mapFogs[ i ].visibleSide >= 0 ) {
				bspFogs[ i ].visibleSide = mapFogs[ i ].visibleSide;
				continue;
			}

			/* find visible side */
			for ( j = 0; j < 6; j++ )
			{
				if ( mapFogs[ i ].brush->sides[ j ].visibleHull != NULL ) {
					Sys_Printf( "Fog %d has visible side %d\n", i, j );
					bspFogs[ i ].visibleSide = j;
					break;
				}
			}
		}
	}
}