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
struct TYPE_4__ {void* length; void* offset; } ;
typedef  TYPE_1__ bspLump_t ;
struct TYPE_5__ {TYPE_1__* lumps; } ;
typedef  TYPE_2__ bspHeader_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 void* LittleLong (int) ; 
 int /*<<< orphan*/  SafeWrite (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int ftell (int /*<<< orphan*/ *) ; 

void AddLump( FILE *file, bspHeader_t *header, int lumpNum, const void *data, int length ){
	bspLump_t   *lump;
	char pad[3] = {'\0', '\0', '\0'};
	unsigned int lengthU = length;
	unsigned int padLength = ((lengthU + 3) / 4) * 4 - lengthU;


	/* add lump to bsp file header */
	lump = &header->lumps[ lumpNum ];
	lump->offset = LittleLong( ftell( file ) );
	lump->length = LittleLong( length );

	/* write lump to file */
	SafeWrite( file, data, length );
	if ( padLength != 0 ) {
		SafeWrite( file, pad, padLength );
	}
}