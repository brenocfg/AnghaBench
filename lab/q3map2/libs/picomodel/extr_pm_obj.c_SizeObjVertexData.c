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
typedef  int /*<<< orphan*/  TObjVertexData ;

/* Variables and functions */
 int SIZE_OBJ_STEP ; 
 scalar_t__ _pico_alloc (int) ; 
 scalar_t__ _pico_realloc (void*,int,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static TObjVertexData *SizeObjVertexData(
	TObjVertexData *vertexData, int reqEntries,
	int *entries, int *allocated ){
	int newAllocated;

	/* sanity checks */
	if ( reqEntries < 1 ) {
		return NULL;
	}
	if ( entries == NULL || allocated == NULL ) {
		return NULL; /* must have */

	}
	/* no need to grow yet */
	if ( vertexData && ( reqEntries < *allocated ) ) {
		*entries = reqEntries;
		return vertexData;
	}
	/* given vertex data ptr not allocated yet */
	if ( vertexData == NULL ) {
		/* how many entries to allocate */
		newAllocated = ( reqEntries > SIZE_OBJ_STEP ) ?
					   reqEntries : SIZE_OBJ_STEP;

		/* throw out an extended debug message */
#ifdef DEBUG_PM_OBJ_EX
		printf( "SizeObjVertexData: allocate (%d entries)\n",
				newAllocated );
#endif
		/* first time allocation */
		vertexData = (TObjVertexData *)
					 _pico_alloc( sizeof( TObjVertexData ) * newAllocated );

		/* allocation failed */
		if ( vertexData == NULL ) {
			return NULL;
		}

		/* allocation succeeded */
		*allocated = newAllocated;
		*entries   = reqEntries;
		return vertexData;
	}
	/* given vertex data ptr needs to be resized */
	if ( reqEntries == *allocated ) {
		newAllocated = ( *allocated + SIZE_OBJ_STEP );

		/* throw out an extended debug message */
#ifdef DEBUG_PM_OBJ_EX
		printf( "SizeObjVertexData: reallocate (%d entries)\n",
				newAllocated );
#endif
		/* try to reallocate */
		vertexData = (TObjVertexData *)
					 _pico_realloc( (void *)&vertexData,
									sizeof( TObjVertexData ) * ( *allocated ),
									sizeof( TObjVertexData ) * ( newAllocated ) );

		/* reallocation failed */
		if ( vertexData == NULL ) {
			return NULL;
		}

		/* reallocation succeeded */
		*allocated = newAllocated;
		*entries   = reqEntries;
		return vertexData;
	}
	/* we're b0rked when we reach this */
	return NULL;
}