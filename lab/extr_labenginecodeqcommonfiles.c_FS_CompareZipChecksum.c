#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_4__ {int checksum; } ;
typedef  TYPE_1__ pack_t ;

/* Variables and functions */
 int /*<<< orphan*/  FS_FreePak (TYPE_1__*) ; 
 TYPE_1__* FS_LoadZipFile (char const*,char*) ; 
 int fs_numServerReferencedPaks ; 
 int* fs_serverReferencedPaks ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean FS_CompareZipChecksum(const char *zipfile)
{
	pack_t *thepak;
	int index, checksum;

	thepak = FS_LoadZipFile(zipfile, "");

	if(!thepak)
		return qfalse;

	checksum = thepak->checksum;
	FS_FreePak(thepak);

	for(index = 0; index < fs_numServerReferencedPaks; index++)
	{
		if(checksum == fs_serverReferencedPaks[index])
			return qtrue;
	}

	return qfalse;
}