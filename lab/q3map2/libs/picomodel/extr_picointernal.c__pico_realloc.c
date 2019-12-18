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

/* Variables and functions */
 void* _pico_alloc (size_t) ; 
 int /*<<< orphan*/  _pico_free (void*) ; 
 int /*<<< orphan*/ * _pico_ptr_malloc ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

void *_pico_realloc( void **ptr, size_t oldSize, size_t newSize ){
	void *ptr2;

	/* sanity checks */
	if ( ptr == NULL ) {
		return NULL;
	}
	if ( newSize < oldSize ) {
		return *ptr;
	}
	if ( _pico_ptr_malloc == NULL ) {
		return NULL;
	}

	/* allocate new pointer */
	ptr2 = _pico_alloc( newSize );
	if ( ptr2 == NULL ) {
		return NULL;
	}

	/* copy */
	if ( *ptr != NULL ) {
		memcpy( ptr2, *ptr, oldSize );
		_pico_free( *ptr );
	}

	/* fix up and return */
	*ptr = ptr2;
	return *ptr;
}