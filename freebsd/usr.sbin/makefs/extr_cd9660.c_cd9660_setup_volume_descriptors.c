#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned char* volumeDescriptorData; int sector; struct TYPE_7__* next; } ;
typedef  TYPE_1__ volume_descriptor ;
struct TYPE_8__ {scalar_t__ verbose_level; scalar_t__ is_bootable; TYPE_1__* firstVolumeDescriptor; int /*<<< orphan*/  primaryDescriptor; } ;
typedef  TYPE_2__ iso9660_disk ;

/* Variables and functions */
 unsigned char ISO_VOLUME_DESCRIPTOR_PVD ; 
 int /*<<< orphan*/  ISO_VOLUME_DESCRIPTOR_STANDARD_ID ; 
 int ISO_VOLUME_DESCRIPTOR_TERMINATOR ; 
 int /*<<< orphan*/  cd9660_setup_boot_volume_descriptor (TYPE_2__*,TYPE_1__*) ; 
 void* ecalloc (int,int) ; 
 TYPE_1__* emalloc (int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
cd9660_setup_volume_descriptors(iso9660_disk *diskStructure)
{
	/* Boot volume descriptor should come second */
	int sector = 16;
	/* For now, a fixed 2 : PVD and terminator */
	volume_descriptor *temp, *t;

	/* Set up the PVD */
	temp = emalloc(sizeof(*temp));
	temp->volumeDescriptorData =
	   (unsigned char *)&diskStructure->primaryDescriptor;
	temp->volumeDescriptorData[0] = ISO_VOLUME_DESCRIPTOR_PVD;
	temp->volumeDescriptorData[6] = 1;
	temp->sector = sector;
	memcpy(temp->volumeDescriptorData + 1,
	    ISO_VOLUME_DESCRIPTOR_STANDARD_ID, 5);
	diskStructure->firstVolumeDescriptor = temp;

	sector++;
	/* Set up boot support if enabled. BVD must reside in sector 17 */
	if (diskStructure->is_bootable) {
		t = emalloc(sizeof(*t));
		t->volumeDescriptorData = ecalloc(1, 2048);
		temp->next = t;
		temp = t;
		t->sector = 17;
		if (diskStructure->verbose_level > 0)
			printf("Setting up boot volume descriptor\n");
		cd9660_setup_boot_volume_descriptor(diskStructure, t);
		sector++;
	}

	/* Set up the terminator */
	t = emalloc(sizeof(*t));
	t->volumeDescriptorData = ecalloc(1, 2048);
	temp->next = t;
	t->volumeDescriptorData[0] = ISO_VOLUME_DESCRIPTOR_TERMINATOR;
	t->next = NULL;
	t->volumeDescriptorData[6] = 1;
	t->sector = sector;
	memcpy(t->volumeDescriptorData + 1,
	    ISO_VOLUME_DESCRIPTOR_STANDARD_ID, 5);

	sector++;
	return sector;
}