#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int* length; unsigned char* name; int /*<<< orphan*/  parent_number; int /*<<< orphan*/  first_sector; int /*<<< orphan*/ * extended_attribute_length; } ;
typedef  TYPE_3__ path_table_entry ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_13__ {TYPE_5__* rootNode; int /*<<< orphan*/  sectorSize; int /*<<< orphan*/  pathTableLength; } ;
typedef  TYPE_4__ iso9660_disk ;
struct TYPE_14__ {struct TYPE_14__* ptnext; TYPE_2__* parent; int /*<<< orphan*/  fileDataSector; TYPE_1__* isoDirRecord; } ;
typedef  TYPE_5__ cd9660node ;
struct TYPE_11__ {int ptnumber; } ;
struct TYPE_10__ {int* name_len; TYPE_3__* name; int /*<<< orphan*/ * ext_attr_length; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CD9660_BLOCKS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LITTLE_ENDIAN ; 
 int /*<<< orphan*/  cd9660_721 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cd9660_722 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cd9660_731 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cd9660_732 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cd9660_write_filedata (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,int) ; 
 unsigned char* ecalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
cd9660_write_path_table(iso9660_disk *diskStructure, FILE *fd, off_t sector,
    int mode)
{
	int path_table_sectors = CD9660_BLOCKS(diskStructure->sectorSize,
	    diskStructure->pathTableLength);
	unsigned char *buffer;
	unsigned char *buffer_head;
	int len, ret;
	path_table_entry temp_entry;
	cd9660node *ptcur;

	buffer = ecalloc(path_table_sectors, diskStructure->sectorSize);
	buffer_head = buffer;

	ptcur = diskStructure->rootNode;

	while (ptcur != NULL) {
		memset(&temp_entry, 0, sizeof(path_table_entry));
		temp_entry.length[0] = ptcur->isoDirRecord->name_len[0];
		temp_entry.extended_attribute_length[0] =
		    ptcur->isoDirRecord->ext_attr_length[0];
		memcpy(temp_entry.name, ptcur->isoDirRecord->name,
		    temp_entry.length[0] + 1);

		/* round up */
		len = temp_entry.length[0] + 8 + (temp_entry.length[0] & 0x01);

                /* todo: function pointers instead */
		if (mode == LITTLE_ENDIAN) {
			cd9660_731(ptcur->fileDataSector,
			    temp_entry.first_sector);
			cd9660_721((ptcur->parent == NULL ?
				1 : ptcur->parent->ptnumber),
			    temp_entry.parent_number);
		} else {
			cd9660_732(ptcur->fileDataSector,
			    temp_entry.first_sector);
			cd9660_722((ptcur->parent == NULL ?
				1 : ptcur->parent->ptnumber),
			    temp_entry.parent_number);
		}


		memcpy(buffer, &temp_entry, len);
		buffer += len;

		ptcur = ptcur->ptnext;
	}

	ret = cd9660_write_filedata(diskStructure, fd, sector, buffer_head,
	    path_table_sectors);
	free(buffer_head);
	return ret;
}