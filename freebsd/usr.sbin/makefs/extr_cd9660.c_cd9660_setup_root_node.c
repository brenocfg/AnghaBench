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
struct TYPE_5__ {TYPE_1__* rootNode; } ;
typedef  TYPE_2__ iso9660_disk ;
struct TYPE_4__ {int /*<<< orphan*/  isoDirRecord; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISO_FLAG_DIRECTORY ; 
 int /*<<< orphan*/  cd9660_populate_iso_dir_record (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static void
cd9660_setup_root_node(iso9660_disk *diskStructure)
{
	cd9660_populate_iso_dir_record(diskStructure->rootNode->isoDirRecord,
	    0, ISO_FLAG_DIRECTORY, 1, "\0");

}