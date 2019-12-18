#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* rootNode; } ;
typedef  TYPE_2__ iso9660_disk ;
struct TYPE_11__ {TYPE_8__* dot_dot_record; TYPE_1__* parent; int /*<<< orphan*/  isoDirRecord; int /*<<< orphan*/  fileDataSector; TYPE_8__* dot_record; } ;
typedef  TYPE_3__ cd9660node ;
struct TYPE_13__ {void* fileRecordSize; TYPE_4__* isoDirRecord; int /*<<< orphan*/  fileDataSector; } ;
struct TYPE_12__ {int* name_len; int* name; int* length; } ;
struct TYPE_9__ {int /*<<< orphan*/  isoDirRecord; int /*<<< orphan*/  fileDataSector; } ;

/* Variables and functions */
 void* cd9660_compute_record_size (TYPE_2__*,TYPE_8__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cd9660_populate_dot_records(iso9660_disk *diskStructure, cd9660node *node)
{
	node->dot_record->fileDataSector = node->fileDataSector;
	memcpy(node->dot_record->isoDirRecord,node->isoDirRecord, 34);
	node->dot_record->isoDirRecord->name_len[0] = 1;
	node->dot_record->isoDirRecord->name[0] = 0;
	node->dot_record->isoDirRecord->name[1] = 0;
	node->dot_record->isoDirRecord->length[0] = 34;
	node->dot_record->fileRecordSize =
	    cd9660_compute_record_size(diskStructure, node->dot_record);

	if (node == diskStructure->rootNode) {
		node->dot_dot_record->fileDataSector = node->fileDataSector;
		memcpy(node->dot_dot_record->isoDirRecord,node->isoDirRecord,
		    34);
	} else {
		node->dot_dot_record->fileDataSector =
		    node->parent->fileDataSector;
		memcpy(node->dot_dot_record->isoDirRecord,
		    node->parent->isoDirRecord,34);
	}
	node->dot_dot_record->isoDirRecord->name_len[0] = 1;
	node->dot_dot_record->isoDirRecord->name[0] = 1;
	node->dot_dot_record->isoDirRecord->name[1] = 0;
	node->dot_dot_record->isoDirRecord->length[0] = 34;
	node->dot_dot_record->fileRecordSize =
	    cd9660_compute_record_size(diskStructure, node->dot_dot_record);
}