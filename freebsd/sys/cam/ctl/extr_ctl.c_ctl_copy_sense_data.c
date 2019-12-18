#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  status; } ;
struct TYPE_8__ {int /*<<< orphan*/  sense_len; int /*<<< orphan*/  scsi_status; int /*<<< orphan*/  sense_data; } ;
union ctl_io {TYPE_1__ io_hdr; TYPE_4__ scsiio; } ;
struct TYPE_6__ {int /*<<< orphan*/  status; } ;
struct TYPE_7__ {int /*<<< orphan*/  sense_len; int /*<<< orphan*/  scsi_status; int /*<<< orphan*/  sense_data; } ;
union ctl_ha_msg {TYPE_2__ hdr; TYPE_3__ scsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ctl_copy_sense_data(union ctl_ha_msg *src, union ctl_io *dest)
{

	memcpy(&dest->scsiio.sense_data, &src->scsi.sense_data,
	    src->scsi.sense_len);
	dest->scsiio.scsi_status = src->scsi.scsi_status;
	dest->scsiio.sense_len = src->scsi.sense_len;
	dest->io_hdr.status = src->hdr.status;
}