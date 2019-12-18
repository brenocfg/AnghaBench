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
typedef  int uint16_t ;
struct ctl_scsiio {int dummy; } ;
typedef  int /*<<< orphan*/  sks ;

/* Variables and functions */
 int /*<<< orphan*/  SSD_ELEM_NONE ; 
 int /*<<< orphan*/  SSD_ELEM_SKIP ; 
 int /*<<< orphan*/  SSD_ELEM_SKS ; 
 int /*<<< orphan*/  SSD_KEY_HARDWARE_ERROR ; 
 int SSD_SCS_VALID ; 
 int /*<<< orphan*/  ctl_set_sense (struct ctl_scsiio*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 

void
ctl_set_internal_failure(struct ctl_scsiio *ctsio, int sks_valid,
			 uint16_t retry_count)
{
	uint8_t sks[3];

	if (sks_valid) {
		sks[0] = SSD_SCS_VALID;
		sks[1] = (retry_count >> 8) & 0xff;
		sks[2] = retry_count & 0xff;
	}

	/* "Internal target failure" */
	ctl_set_sense(ctsio,
		      /*current_error*/ 1,
		      /*sense_key*/ SSD_KEY_HARDWARE_ERROR,
		      /*asc*/ 0x44,
		      /*ascq*/ 0x00,
		      /*type*/ (sks_valid != 0) ? SSD_ELEM_SKS : SSD_ELEM_SKIP,
		      /*size*/ sizeof(sks),
		      /*data*/ sks,
		      SSD_ELEM_NONE);
}