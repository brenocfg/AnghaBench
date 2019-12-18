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
 void* _pico_ptr_malloc (size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

void *_pico_alloc( size_t size ){
	void *ptr;

	/* some sanity checks */
	if ( size == 0 ) {
		return NULL;
	}
	if ( _pico_ptr_malloc == NULL ) {
		return NULL;
	}

	/* allocate memory */
	ptr = _pico_ptr_malloc( size );
	if ( ptr == NULL ) {
		return NULL;
	}

	/* zero out allocated memory */
	memset( ptr,0,size );

	/* return pointer to allocated memory */
	return ptr;
}