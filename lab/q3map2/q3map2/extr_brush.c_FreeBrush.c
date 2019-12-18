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
struct TYPE_7__ {int numsides; TYPE_1__* sides; } ;
typedef  TYPE_2__ brush_t ;
struct TYPE_6__ {int /*<<< orphan*/ * winding; } ;

/* Variables and functions */
 int /*<<< orphan*/  FreeWinding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_VRB ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  numActiveBrushes ; 
 int numthreads ; 

void FreeBrush( brush_t *b ){
	int i;


	/* error check */
	if ( *( (unsigned int*) b ) == 0xFEFEFEFE ) {
		Sys_FPrintf( SYS_VRB, "WARNING: Attempt to free an already freed brush!\n" );
		return;
	}

	/* free brush sides */
	for ( i = 0; i < b->numsides; i++ )
		if ( b->sides[i].winding != NULL ) {
			FreeWinding( b->sides[ i ].winding );
		}

	/* ydnar: overwrite it */
	memset( b, 0xFE, sizeof( *b ) + sizeof( *b->sides ) * b->numsides );
	*( (unsigned int*) b ) = 0xFEFEFEFE;

	/* free it */
	free( b );
	if ( numthreads == 1 ) {
		numActiveBrushes--;
	}
}