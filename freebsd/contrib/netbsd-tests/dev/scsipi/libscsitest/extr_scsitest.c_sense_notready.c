#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_sense_data {int response_code; int asc; int ascq; int extra_len; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {struct scsi_sense_data scsi_sense; } ;
struct scsipi_xfer {int /*<<< orphan*/  error; TYPE_1__ sense; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKEY_NOT_READY ; 
 int /*<<< orphan*/  XS_SENSE ; 

__attribute__((used)) static void
sense_notready(struct scsipi_xfer *xs)
{
	struct scsi_sense_data *sense = &xs->sense.scsi_sense;

	xs->error = XS_SENSE;

	sense->response_code = 0x70;
	sense->flags = SKEY_NOT_READY;
	sense->asc = 0x3A;
	sense->ascq = 0x00;
	sense->extra_len = 6;
}