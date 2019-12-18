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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  ocs_textbuf_t ;
typedef  int /*<<< orphan*/  ocs_t ;

/* Variables and functions */
 int /*<<< orphan*/  MGMT_MODE_RD ; 
 int /*<<< orphan*/  OCS_SCSI_SERIALNUMBER ; 
 int /*<<< orphan*/  ocs_mgmt_emit_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * ocs_scsi_get_property_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 

__attribute__((used)) static void
get_sn(ocs_t *ocs, char *name, ocs_textbuf_t *textbuf)
{
	uint8_t *pserial;
	uint32_t len;
	char sn_buf[256];

	pserial = ocs_scsi_get_property_ptr(ocs, OCS_SCSI_SERIALNUMBER);
	if (pserial) {
		len = *pserial ++;
		strncpy(sn_buf, (char*)pserial, len);
		sn_buf[len] = '\0';
		ocs_mgmt_emit_string(textbuf, MGMT_MODE_RD, "sn", sn_buf);
	}
}