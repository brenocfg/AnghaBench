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
struct TYPE_4__ {int /*<<< orphan*/  primaryBigEndianTableSector; int /*<<< orphan*/  primaryLittleEndianTableSector; } ;
typedef  TYPE_1__ iso9660_disk ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BIG_ENDIAN ; 
 int /*<<< orphan*/  LITTLE_ENDIAN ; 
 scalar_t__ cd9660_write_path_table (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cd9660_write_path_tables(iso9660_disk *diskStructure, FILE *fd)
{
	if (cd9660_write_path_table(diskStructure, fd,
	    diskStructure->primaryLittleEndianTableSector, LITTLE_ENDIAN) == 0)
		return 0;

	if (cd9660_write_path_table(diskStructure, fd,
	    diskStructure->primaryBigEndianTableSector, BIG_ENDIAN) == 0)
		return 0;

	/* @TODO: handle remaining two path tables */
	return 1;
}