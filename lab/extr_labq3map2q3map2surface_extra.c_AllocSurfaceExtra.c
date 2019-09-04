#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  surfaceExtra_t ;

/* Variables and functions */
 scalar_t__ GROW_SURFACE_EXTRAS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int maxSurfaceExtras ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int numSurfaceExtras ; 
 int /*<<< orphan*/ * safe_malloc (int) ; 
 int /*<<< orphan*/  seDefault ; 
 int /*<<< orphan*/ * surfaceExtras ; 

__attribute__((used)) static surfaceExtra_t *AllocSurfaceExtra( void ){
	surfaceExtra_t  *se;


	/* enough space? */
	if ( numSurfaceExtras >= maxSurfaceExtras ) {
		/* reallocate more room */
		maxSurfaceExtras += GROW_SURFACE_EXTRAS;
		se = safe_malloc( maxSurfaceExtras * sizeof( surfaceExtra_t ) );
		if ( surfaceExtras != NULL ) {
			memcpy( se, surfaceExtras, numSurfaceExtras * sizeof( surfaceExtra_t ) );
			free( surfaceExtras );
		}
		surfaceExtras = se;
	}

	/* add another */
	se = &surfaceExtras[ numSurfaceExtras ];
	numSurfaceExtras++;
	memcpy( se, &seDefault, sizeof( surfaceExtra_t ) );

	/* return it */
	return se;
}