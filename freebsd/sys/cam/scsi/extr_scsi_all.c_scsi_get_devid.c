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
typedef  int uint32_t ;
struct scsi_vpd_id_descriptor {int dummy; } ;
struct scsi_vpd_device_id {scalar_t__ desc_list; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  scsi_devid_checkfn_t ;

/* Variables and functions */
 int MIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_2btoul (int /*<<< orphan*/ ) ; 
 struct scsi_vpd_id_descriptor* scsi_get_devid_desc (struct scsi_vpd_id_descriptor*,int,int /*<<< orphan*/ ) ; 

struct scsi_vpd_id_descriptor *
scsi_get_devid(struct scsi_vpd_device_id *id, uint32_t page_len,
    scsi_devid_checkfn_t ck_fn)
{
	uint32_t len;

	if (page_len < sizeof(*id))
		return (NULL);
	len = MIN(scsi_2btoul(id->length), page_len - sizeof(*id));
	return (scsi_get_devid_desc((struct scsi_vpd_id_descriptor *)
	    id->desc_list, len, ck_fn));
}