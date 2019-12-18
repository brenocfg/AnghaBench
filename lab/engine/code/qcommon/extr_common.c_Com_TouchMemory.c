#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int size; struct TYPE_5__* next; scalar_t__ tag; } ;
typedef  TYPE_1__ memblock_t ;
struct TYPE_8__ {int permanent; } ;
struct TYPE_7__ {int permanent; } ;
struct TYPE_6__ {TYPE_1__ blocklist; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*,int) ; 
 int Sys_Milliseconds () ; 
 int /*<<< orphan*/  Z_CheckHeap () ; 
 TYPE_4__ hunk_high ; 
 TYPE_3__ hunk_low ; 
 TYPE_2__* mainzone ; 
 scalar_t__ s_hunkData ; 
 int s_hunkTotal ; 

void Com_TouchMemory( void ) {
	int		start, end;
	int		i, j;
	unsigned	sum;
	memblock_t	*block;

	Z_CheckHeap();

	start = Sys_Milliseconds();

	sum = 0;

	j = hunk_low.permanent >> 2;
	for ( i = 0 ; i < j ; i+=64 ) {			// only need to touch each page
		sum += ((int *)s_hunkData)[i];
	}

	i = ( s_hunkTotal - hunk_high.permanent ) >> 2;
	j = hunk_high.permanent >> 2;
	for (  ; i < j ; i+=64 ) {			// only need to touch each page
		sum += ((int *)s_hunkData)[i];
	}

	for (block = mainzone->blocklist.next ; ; block = block->next) {
		if ( block->tag ) {
			j = block->size >> 2;
			for ( i = 0 ; i < j ; i+=64 ) {				// only need to touch each page
				sum += ((int *)block)[i];
			}
		}
		if ( block->next == &mainzone->blocklist ) {
			break;			// all blocks have been hit	
		}
	}

	end = Sys_Milliseconds();

	Com_Printf( "Com_TouchMemory: %i msec\n", end - start );
}