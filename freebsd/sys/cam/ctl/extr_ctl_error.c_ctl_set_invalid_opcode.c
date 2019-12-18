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
typedef  int uint8_t ;
struct ctl_scsiio {int dummy; } ;
typedef  int /*<<< orphan*/  sks ;

/* Variables and functions */
 int /*<<< orphan*/  SSD_ELEM_NONE ; 
 int /*<<< orphan*/  SSD_ELEM_SKS ; 
 int SSD_FIELDPTR_CMD ; 
 int /*<<< orphan*/  SSD_KEY_ILLEGAL_REQUEST ; 
 int SSD_SCS_VALID ; 
 int /*<<< orphan*/  ctl_set_sense (struct ctl_scsiio*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto2b (int /*<<< orphan*/ ,int*) ; 

void
ctl_set_invalid_opcode(struct ctl_scsiio *ctsio)
{
	uint8_t sks[3];

	sks[0] = SSD_SCS_VALID | SSD_FIELDPTR_CMD;
	scsi_ulto2b(0, &sks[1]);

	/* "Invalid command operation code" */
	ctl_set_sense(ctsio,
		      /*current_error*/ 1,
		      /*sense_key*/ SSD_KEY_ILLEGAL_REQUEST,
		      /*asc*/ 0x20,
		      /*ascq*/ 0x00,
		      /*type*/ SSD_ELEM_SKS,
		      /*size*/ sizeof(sks),
		      /*data*/ sks,
		      SSD_ELEM_NONE);
}