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
 int SSD_BITPTR_VALID ; 
 int /*<<< orphan*/  SSD_ELEM_NONE ; 
 int /*<<< orphan*/  SSD_ELEM_SKIP ; 
 int /*<<< orphan*/  SSD_ELEM_SKS ; 
 int SSD_FIELDPTR_CMD ; 
 int /*<<< orphan*/  SSD_KEY_ILLEGAL_REQUEST ; 
 int SSD_SCS_VALID ; 
 int /*<<< orphan*/  ctl_set_sense (struct ctl_scsiio*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto2b (int,int*) ; 

void
ctl_set_invalid_field(struct ctl_scsiio *ctsio, int sks_valid, int command,
		      int field, int bit_valid, int bit)
{
	uint8_t sks[3];
	int asc;

	if (command != 0) {
		/* "Invalid field in CDB" */
		asc = 0x24;
	} else {
		/* "Invalid field in parameter list" */
		asc = 0x26;
	}

	if (sks_valid) {
		sks[0] = SSD_SCS_VALID;
		if (command)
			sks[0] |= SSD_FIELDPTR_CMD;
		scsi_ulto2b(field, &sks[1]);

		if (bit_valid)
			sks[0] |= SSD_BITPTR_VALID | bit;
	}

	ctl_set_sense(ctsio,
		      /*current_error*/ 1,
		      /*sense_key*/ SSD_KEY_ILLEGAL_REQUEST,
		      asc,
		      /*ascq*/ 0x00,
		      /*type*/ (sks_valid != 0) ? SSD_ELEM_SKS : SSD_ELEM_SKIP,
		      /*size*/ sizeof(sks),
		      /*data*/ sks,
		      SSD_ELEM_NONE);
}