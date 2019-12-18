#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_8__ {int* root_directory_record; int* file_structure_version; scalar_t__ effective_date; scalar_t__* expiration_date; scalar_t__ modification_date; scalar_t__ creation_date; int /*<<< orphan*/  bibliographic_file_id; int /*<<< orphan*/  abstract_file_id; int /*<<< orphan*/  copyright_file_id; int /*<<< orphan*/  application_id; int /*<<< orphan*/  preparer_id; int /*<<< orphan*/  publisher_id; int /*<<< orphan*/  volume_set_id; int /*<<< orphan*/  system_id; int /*<<< orphan*/  volume_id; scalar_t__ type_m_path_table; scalar_t__ type_l_path_table; scalar_t__ path_table_size; scalar_t__ logical_block_size; scalar_t__ volume_sequence_number; scalar_t__ volume_set_size; scalar_t__ volume_space_size; } ;
struct TYPE_11__ {int sectorSize; TYPE_3__* rootNode; TYPE_1__ primaryDescriptor; int /*<<< orphan*/  primaryBigEndianTableSector; int /*<<< orphan*/  primaryLittleEndianTableSector; int /*<<< orphan*/  pathTableLength; int /*<<< orphan*/  totalSectors; } ;
typedef  TYPE_4__ iso9660_disk ;
struct TYPE_13__ {int /*<<< orphan*/  date; } ;
struct TYPE_12__ {int /*<<< orphan*/  st_mtime; scalar_t__ st_ino; } ;
struct TYPE_10__ {TYPE_2__* dot_record; } ;
struct TYPE_9__ {TYPE_6__* isoDirRecord; } ;

/* Variables and functions */
 int /*<<< orphan*/  cd9660_731 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cd9660_732 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cd9660_bothendian_dword (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  cd9660_bothendian_word (int,unsigned char*) ; 
 int /*<<< orphan*/  cd9660_pad_string_spaces (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cd9660_set_date (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cd9660_time_8426 (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cd9660_time_915 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 TYPE_5__ stampst ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cd9660_finalize_PVD(iso9660_disk *diskStructure)
{
	time_t tstamp = stampst.st_ino ? stampst.st_mtime : time(NULL);

	/* root should be a fixed size of 34 bytes since it has no name */
	memcpy(diskStructure->primaryDescriptor.root_directory_record,
		diskStructure->rootNode->dot_record->isoDirRecord, 34);

	/* In RRIP, this might be longer than 34 */
	diskStructure->primaryDescriptor.root_directory_record[0] = 34;

	/* Set up all the important numbers in the PVD */
	cd9660_bothendian_dword(diskStructure->totalSectors,
	    (unsigned char *)diskStructure->primaryDescriptor.volume_space_size);
	cd9660_bothendian_word(1,
	    (unsigned char *)diskStructure->primaryDescriptor.volume_set_size);
	cd9660_bothendian_word(1,
	    (unsigned char *)
		diskStructure->primaryDescriptor.volume_sequence_number);
	cd9660_bothendian_word(diskStructure->sectorSize,
	    (unsigned char *)
		diskStructure->primaryDescriptor.logical_block_size);
	cd9660_bothendian_dword(diskStructure->pathTableLength,
	    (unsigned char *)diskStructure->primaryDescriptor.path_table_size);

	cd9660_731(diskStructure->primaryLittleEndianTableSector,
		(u_char *)diskStructure->primaryDescriptor.type_l_path_table);
	cd9660_732(diskStructure->primaryBigEndianTableSector,
		(u_char *)diskStructure->primaryDescriptor.type_m_path_table);

	diskStructure->primaryDescriptor.file_structure_version[0] = 1;

	/* Pad all strings with spaces instead of nulls */
	cd9660_pad_string_spaces(diskStructure->primaryDescriptor.volume_id, 32);
	cd9660_pad_string_spaces(diskStructure->primaryDescriptor.system_id, 32);
	cd9660_pad_string_spaces(diskStructure->primaryDescriptor.volume_set_id,
	    128);
	cd9660_pad_string_spaces(diskStructure->primaryDescriptor.publisher_id,
	    128);
	cd9660_pad_string_spaces(diskStructure->primaryDescriptor.preparer_id,
	    128);
	cd9660_pad_string_spaces(diskStructure->primaryDescriptor.application_id,
	    128);
	cd9660_pad_string_spaces(
	    diskStructure->primaryDescriptor.copyright_file_id, 37);
	cd9660_pad_string_spaces(
		diskStructure->primaryDescriptor.abstract_file_id, 37);
	cd9660_pad_string_spaces(
		diskStructure->primaryDescriptor.bibliographic_file_id, 37);

	/* Setup dates */
	cd9660_time_8426(
	    (unsigned char *)diskStructure->primaryDescriptor.creation_date,
	    tstamp);
	cd9660_time_8426(
	    (unsigned char *)diskStructure->primaryDescriptor.modification_date,
	    tstamp);

#if 0
	cd9660_set_date(diskStructure->primaryDescriptor.expiration_date,
	    tstamp);
#endif

	memset(diskStructure->primaryDescriptor.expiration_date, '0', 16);
	diskStructure->primaryDescriptor.expiration_date[16] = 0;

	cd9660_time_8426(
	    (unsigned char *)diskStructure->primaryDescriptor.effective_date,
	    tstamp);
	/* make this sane */
	cd9660_time_915(diskStructure->rootNode->dot_record->isoDirRecord->date,
	    tstamp);
}