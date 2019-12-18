#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picoIndex_t ;
struct TYPE_6__ {int a; int c; int b; int visible; } ;
struct TYPE_5__ {int /*<<< orphan*/  surface; } ;
typedef  TYPE_1__ T3dsLoaderPers ;
typedef  TYPE_2__ T3dsIndices ;

/* Variables and functions */
 void* GetWord (TYPE_1__*) ; 
 int /*<<< orphan*/  PicoSetSurfaceIndex (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static int GetMeshFaces( T3dsLoaderPers *pers ){
	int numFaces;
	int i;

	/* get number of faces for this surface */
	numFaces = GetWord( pers );

#ifdef DEBUG_PM_3DS
	printf( "GetMeshFaces: numfaces %d\n",numFaces );
#endif
	/* read in vertex indices for current surface */
	for ( i = 0; i < numFaces; i++ )
	{
		/* remember, we only need 3 of 4 values read in for each */
		/* face. the 4th value is a vis flag for 3dsmax which is */
		/* being ignored by us here */
		T3dsIndices face;
		face.a       = GetWord( pers );
		face.c       = GetWord( pers );   /* ydnar: flipped order */
		face.b       = GetWord( pers );   /* ydnar: flipped order */
		face.visible = GetWord( pers );

		/* copy indexes */
		PicoSetSurfaceIndex( pers->surface, ( i * 3 + 0 ), (picoIndex_t)face.a );
		PicoSetSurfaceIndex( pers->surface, ( i * 3 + 1 ), (picoIndex_t)face.b );
		PicoSetSurfaceIndex( pers->surface, ( i * 3 + 2 ), (picoIndex_t)face.c );

#ifdef DEBUG_PM_3DS_EX
		printf( "Face: a: %d b: %d c: %d (%d)\n",face.a,face.b,face.c,face.visible );
#endif
	}
	/* success (no errors occured) */
	return 1;
}