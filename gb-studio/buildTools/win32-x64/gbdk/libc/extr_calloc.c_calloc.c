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
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

void *calloc( int nmem, int size )
{
	void *malloced;

	malloced = malloc( nmem*size );
	if (malloced!=NULL) {
		memset( malloced, 0, nmem*size );
		return malloced;
	}
	return	NULL;
}