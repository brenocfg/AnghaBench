#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fileHandle_t ;
struct TYPE_5__ {void* filelen; void* fileofs; } ;
typedef  TYPE_1__ aas_lump_t ;
struct TYPE_6__ {TYPE_1__* lumps; } ;
typedef  TYPE_2__ aas_header_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* FS_Write ) (void*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int AAS_WriteAASLump_offset ; 
 void* LittleLong (int) ; 
 TYPE_3__ botimport ; 
 int qtrue ; 
 int /*<<< orphan*/  stub1 (void*,int,int /*<<< orphan*/ ) ; 

int AAS_WriteAASLump(fileHandle_t fp, aas_header_t *h, int lumpnum, void *data, int length)
{
	aas_lump_t *lump;

	lump = &h->lumps[lumpnum];
	
	lump->fileofs = LittleLong(AAS_WriteAASLump_offset);	//LittleLong(ftell(fp));
	lump->filelen = LittleLong(length);

	if (length > 0)
	{
		botimport.FS_Write(data, length, fp );
	} //end if

	AAS_WriteAASLump_offset += length;

	return qtrue;
}