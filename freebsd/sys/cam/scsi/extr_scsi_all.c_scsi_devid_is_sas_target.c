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
struct scsi_vpd_id_descriptor {int id_type; int proto_codeset; } ;

/* Variables and functions */
 int SCSI_PROTO_SAS ; 
 int SVPD_ID_PIV ; 
 int SVPD_ID_PROTO_SHIFT ; 
 int /*<<< orphan*/  scsi_devid_is_naa_ieee_reg (int /*<<< orphan*/ *) ; 

int
scsi_devid_is_sas_target(uint8_t *bufp)
{
	struct scsi_vpd_id_descriptor *descr;

	descr = (struct scsi_vpd_id_descriptor *)bufp;
	if (!scsi_devid_is_naa_ieee_reg(bufp))
		return 0;
	if ((descr->id_type & SVPD_ID_PIV) == 0) /* proto field reserved */
		return 0;
	if ((descr->proto_codeset >> SVPD_ID_PROTO_SHIFT) != SCSI_PROTO_SAS)
		return 0;
	return 1;
}