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
typedef  int /*<<< orphan*/  byte ;
struct TYPE_4__ {TYPE_1__* lumps; } ;
struct TYPE_3__ {int filelen; int fileofs; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int q1_fileLength ; 
 TYPE_2__* q1_header ; 

int Q1_CopyLump (int lump, void *dest, int size, int maxsize)
{
	int		length, ofs;

	length = q1_header->lumps[lump].filelen;
	ofs = q1_header->lumps[lump].fileofs;
	
	if (length % size) {
		Error ("LoadBSPFile: odd lump size");
	}
	// somehow things got out of range
	if ((length/size) > maxsize) {
		printf("WARNING: exceeded max size for lump %d size %d > maxsize %d\n", lump, (length/size), maxsize);
		length = maxsize * size;
	}
	if ( ofs + length > q1_fileLength ) {
		printf("WARNING: exceeded file length for lump %d\n", lump);
		length = q1_fileLength - ofs;
		if ( length <= 0 ) {
			return 0;
		}
	}

	memcpy (dest, (byte *)q1_header + ofs, length);

	return length / size;
}