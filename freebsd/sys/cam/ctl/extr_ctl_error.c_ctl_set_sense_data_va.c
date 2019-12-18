#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
typedef  scalar_t__ u_int ;
struct scsi_sense_data {int dummy; } ;
struct TYPE_4__ {scalar_t__ max_sense; } ;
struct TYPE_3__ {int rlec; } ;
struct ctl_lun {TYPE_2__ MODE_CTRLE; TYPE_1__ MODE_CTRL; } ;
typedef  scalar_t__ scsi_sense_data_type ;

/* Variables and functions */
 int SCP_DSENSE ; 
 scalar_t__ SSD_FULL_SIZE ; 
 scalar_t__ SSD_TYPE_DESC ; 
 scalar_t__ SSD_TYPE_FIXED ; 
 scalar_t__ SSD_TYPE_NONE ; 
 int /*<<< orphan*/  scsi_set_sense_data_va (struct scsi_sense_data*,scalar_t__*,scalar_t__,int,int,int,int,int /*<<< orphan*/ ) ; 

void
ctl_set_sense_data_va(struct scsi_sense_data *sense_data, u_int *sense_len,
    void *lunptr, scsi_sense_data_type sense_format, int current_error,
    int sense_key, int asc, int ascq, va_list ap)
{
	struct ctl_lun *lun;

	lun = (struct ctl_lun *)lunptr;

	/*
	 * Determine whether to return fixed or descriptor format sense
	 * data.
	 */
	if (sense_format == SSD_TYPE_NONE) {
		/*
		 * SPC-3 and up require some UAs to be returned as fixed.
		 */
		if (asc == 0x29 || (asc == 0x2A && ascq == 0x01))
			sense_format = SSD_TYPE_FIXED;
		else
		/*
		 * If the format isn't specified, we only return descriptor
		 * sense if the LUN exists and descriptor sense is turned
		 * on for that LUN.
		 */
		if ((lun != NULL) && (lun->MODE_CTRL.rlec & SCP_DSENSE))
			sense_format = SSD_TYPE_DESC;
		else
			sense_format = SSD_TYPE_FIXED;
	}

	/*
	 * Determine maximum sense data length to return.
	 */
	if (*sense_len == 0) {
		if ((lun != NULL) && (lun->MODE_CTRLE.max_sense != 0))
			*sense_len = lun->MODE_CTRLE.max_sense;
		else
			*sense_len = SSD_FULL_SIZE;
	}

	scsi_set_sense_data_va(sense_data, sense_len, sense_format,
	    current_error, sense_key, asc, ascq, ap);
}