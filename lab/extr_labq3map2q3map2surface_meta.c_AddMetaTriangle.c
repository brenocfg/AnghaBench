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
typedef  int /*<<< orphan*/  metaTriangle_t ;

/* Variables and functions */
 scalar_t__ GROW_META_TRIANGLES ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int maxMetaTriangles ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * metaTriangles ; 
 int numMetaTriangles ; 
 int /*<<< orphan*/ * safe_malloc (int) ; 

__attribute__((used)) static int AddMetaTriangle( void ){
	metaTriangle_t  *temp;


	/* enough space? */
	if ( numMetaTriangles >= maxMetaTriangles ) {
		/* reallocate more room */
		maxMetaTriangles += GROW_META_TRIANGLES;
		temp = safe_malloc( maxMetaTriangles * sizeof( metaTriangle_t ) );
		if ( metaTriangles != NULL ) {
			memcpy( temp, metaTriangles, numMetaTriangles * sizeof( metaTriangle_t ) );
			free( metaTriangles );
		}
		metaTriangles = temp;
	}

	/* increment and return */
	numMetaTriangles++;
	return numMetaTriangles - 1;
}