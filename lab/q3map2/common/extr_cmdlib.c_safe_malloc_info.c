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
 int /*<<< orphan*/  Error (char*,char*,size_t) ; 
 void* calloc (size_t,int) ; 

void *safe_malloc_info( size_t size, char* info ){
	void *p;

	p = calloc( size, 1 );
	if ( !p ) {
		Error( "%s: safe_malloc failed on allocation of %i bytes", info, size );
	}

	return p;
}