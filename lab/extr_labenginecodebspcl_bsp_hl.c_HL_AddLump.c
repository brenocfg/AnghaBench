#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* filelen; void* fileofs; } ;
typedef  TYPE_1__ hl_lump_t ;
struct TYPE_4__ {TYPE_1__* lumps; } ;

/* Variables and functions */
 void* LittleLong (int) ; 
 int /*<<< orphan*/  SafeWrite (int /*<<< orphan*/ ,void*,int) ; 
 int ftell (int /*<<< orphan*/ ) ; 
 TYPE_2__* hl_header ; 
 int /*<<< orphan*/  wadfile ; 

void HL_AddLump (int lumpnum, void *data, int len)
{
	hl_lump_t *lump;

	lump = &hl_header->lumps[lumpnum];
	
	lump->fileofs = LittleLong( ftell(wadfile) );
	lump->filelen = LittleLong(len);
	SafeWrite (wadfile, data, (len+3)&~3);
}