#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ volumeDescriptorData; } ;
typedef  TYPE_1__ volume_descriptor ;
struct TYPE_7__ {TYPE_3__* boot_descriptor; } ;
typedef  TYPE_2__ iso9660_disk ;
struct TYPE_8__ {int* version; int /*<<< orphan*/  identifier; int /*<<< orphan*/  boot_system_identifier; int /*<<< orphan*/ * boot_record_indicator; } ;
typedef  TYPE_3__ boot_volume_descriptor ;

/* Variables and functions */
 int /*<<< orphan*/  ET_ID ; 
 int /*<<< orphan*/  ISO_VOLUME_DESCRIPTOR_BOOT ; 
 int /*<<< orphan*/  ISO_VOLUME_DESCRIPTOR_STANDARD_ID ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
cd9660_setup_boot_volume_descriptor(iso9660_disk *diskStructure,
    volume_descriptor *bvd)
{
	boot_volume_descriptor *bvdData =
	    (boot_volume_descriptor*)bvd->volumeDescriptorData;

	bvdData->boot_record_indicator[0] = ISO_VOLUME_DESCRIPTOR_BOOT;
	memcpy(bvdData->identifier, ISO_VOLUME_DESCRIPTOR_STANDARD_ID, 5);
	bvdData->version[0] = 1;
	memcpy(bvdData->boot_system_identifier, ET_ID, 23);
	memcpy(bvdData->identifier, ISO_VOLUME_DESCRIPTOR_STANDARD_ID, 5);
	diskStructure->boot_descriptor =
	    (boot_volume_descriptor*) bvd->volumeDescriptorData;
	return 1;
}