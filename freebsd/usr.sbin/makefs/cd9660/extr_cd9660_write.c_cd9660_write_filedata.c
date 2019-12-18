#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int off_t ;
struct TYPE_3__ {int sectorSize; } ;
typedef  TYPE_1__ iso9660_disk ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int fseeko (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ftello (int /*<<< orphan*/ *) ; 
 size_t fwrite (unsigned char const*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cd9660_write_filedata(iso9660_disk *diskStructure, FILE *fd, off_t sector,
    const unsigned char *buf, int numsecs)
{
	off_t curpos;
	size_t success;

	curpos = ftello(fd);

	if (fseeko(fd, sector * diskStructure->sectorSize, SEEK_SET) == -1)
		err(1, "fseeko");

	success = fwrite(buf, diskStructure->sectorSize * numsecs, 1, fd);

	if (fseeko(fd, curpos, SEEK_SET) == -1)
		err(1, "fseeko");

	if (success == 1)
		success = diskStructure->sectorSize * numsecs;
	return success;
}