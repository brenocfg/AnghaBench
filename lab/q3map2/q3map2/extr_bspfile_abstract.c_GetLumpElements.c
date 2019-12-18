#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* lumps; } ;
typedef  TYPE_2__ bspHeader_t ;
struct TYPE_4__ {int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,int,int) ; 
 int /*<<< orphan*/  SYS_WRN ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ force ; 

int GetLumpElements( bspHeader_t *header, int lump, int size ){
	/* check for odd size */
	if ( header->lumps[ lump ].length % size ) {
		if ( force ) {
			Sys_FPrintf( SYS_WRN, "WARNING: GetLumpElements: odd lump size (%d) in lump %d\n", header->lumps[ lump ].length, lump );
			return 0;
		}
		else{
			Error( "GetLumpElements: odd lump size (%d) in lump %d", header->lumps[ lump ].length, lump );
		}
	}

	/* return element count */
	return header->lumps[ lump ].length / size;
}