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

/* Variables and functions */
 int DT_STOR_IDE ; 
 int DT_STOR_MMC ; 
 int DT_STOR_SATA ; 
 int DT_STOR_SCSI ; 
 int DT_STOR_USB ; 

char *
ub_stor_type(int type)
{

	if (type & DT_STOR_IDE)
		return ("IDE");

	if (type & DT_STOR_SCSI)
		return ("SCSI");

	if (type & DT_STOR_USB)
		return ("USB");

	if (type & DT_STOR_MMC)
		return ("MMC");

	if (type & DT_STOR_SATA)
		return ("SATA");

	return ("Unknown");
}