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
typedef  int /*<<< orphan*/  uint8_t ;
struct scsi_vpd_id_descriptor {int id_type; } ;

/* Variables and functions */
 int SVPD_ID_ASSOC_LUN ; 
 int SVPD_ID_ASSOC_MASK ; 
 int SVPD_ID_TYPE_MASK ; 
 int SVPD_ID_TYPE_NAA ; 

int
scsi_devid_is_lun_naa(uint8_t *bufp)
{
	struct scsi_vpd_id_descriptor *descr;

	descr = (struct scsi_vpd_id_descriptor *)bufp;
	if ((descr->id_type & SVPD_ID_ASSOC_MASK) != SVPD_ID_ASSOC_LUN)
		return 0;
	if ((descr->id_type & SVPD_ID_TYPE_MASK) != SVPD_ID_TYPE_NAA)
		return 0;
	return 1;
}