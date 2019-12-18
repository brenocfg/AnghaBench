#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/  volumeDescriptorData; int /*<<< orphan*/  sector; } ;
typedef  TYPE_1__ volume_descriptor ;
struct TYPE_6__ {TYPE_1__* firstVolumeDescriptor; } ;
typedef  TYPE_2__ iso9660_disk ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  cd9660_write_filedata (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
cd9660_write_volume_descriptors(iso9660_disk *diskStructure, FILE *fd)
{
	volume_descriptor *vd_temp = diskStructure->firstVolumeDescriptor;

	while (vd_temp != NULL) {
		cd9660_write_filedata(diskStructure, fd, vd_temp->sector,
		    vd_temp->volumeDescriptorData, 1);
		vd_temp = vd_temp->next;
	}
	return 1;
}