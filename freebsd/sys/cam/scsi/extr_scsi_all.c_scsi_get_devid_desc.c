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
typedef  int uint32_t ;
struct scsi_vpd_id_descriptor {int length; int /*<<< orphan*/ * identifier; } ;
typedef  scalar_t__ (* scsi_devid_checkfn_t ) (int /*<<< orphan*/ *) ;

/* Variables and functions */

struct scsi_vpd_id_descriptor *
scsi_get_devid_desc(struct scsi_vpd_id_descriptor *desc, uint32_t len,
    scsi_devid_checkfn_t ck_fn)
{
	uint8_t *desc_buf_end;

	desc_buf_end = (uint8_t *)desc + len;

	for (; desc->identifier <= desc_buf_end &&
	    desc->identifier + desc->length <= desc_buf_end;
	    desc = (struct scsi_vpd_id_descriptor *)(desc->identifier
						    + desc->length)) {

		if (ck_fn == NULL || ck_fn((uint8_t *)desc) != 0)
			return (desc);
	}
	return (NULL);
}