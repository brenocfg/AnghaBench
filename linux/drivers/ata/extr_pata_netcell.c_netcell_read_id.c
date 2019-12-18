#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u16 ;
struct ata_taskfile {int dummy; } ;
struct ata_device {int dummy; } ;

/* Variables and functions */
 size_t ATA_ID_CSF_DEFAULT ; 
 unsigned int ata_do_dev_read_id (struct ata_device*,struct ata_taskfile*,int*) ; 

__attribute__((used)) static unsigned int netcell_read_id(struct ata_device *adev,
					struct ata_taskfile *tf, u16 *id)
{
	unsigned int err_mask = ata_do_dev_read_id(adev, tf, id);
	/* Firmware forgets to mark words 85-87 valid */
	if (err_mask == 0)
		id[ATA_ID_CSF_DEFAULT] |= 0x4000;
	return err_mask;
}