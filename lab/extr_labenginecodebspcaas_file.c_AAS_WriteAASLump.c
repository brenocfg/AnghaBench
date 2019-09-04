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
struct TYPE_4__ {void* filelen; void* fileofs; } ;
typedef  TYPE_1__ aas_lump_t ;
struct TYPE_5__ {TYPE_1__* lumps; } ;
typedef  TYPE_2__ aas_header_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 void* LittleLong (int) ; 
 int /*<<< orphan*/  Log_Print (char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int fwrite (void*,int,int,int /*<<< orphan*/ *) ; 

int AAS_WriteAASLump(FILE *fp, aas_header_t *h, int lumpnum, void *data, int length)
{
	aas_lump_t *lump;

	lump = &h->lumps[lumpnum];
	
	lump->fileofs = LittleLong(ftell(fp));
	lump->filelen = LittleLong(length);

	if (length > 0)
	{
		if (fwrite(data, length, 1, fp) < 1)
		{
			Log_Print("error writing lump %s\n", lumpnum);
			fclose(fp);
			return false;
		} //end if
	} //end if
	return true;
}