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
struct TYPE_2__ {int /*<<< orphan*/  sense_len; int /*<<< orphan*/  sense_data; } ;
union ctl_io {TYPE_1__ scsiio; } ;
typedef  int /*<<< orphan*/  tpc_error_action ;

/* Variables and functions */
#define  SSD_CURRENT_ERROR 134 
#define  SSD_DEFERRED_ERROR 133 
#define  SSD_DESC_CURRENT_ERROR 132 
#define  SSD_DESC_DEFERRED_ERROR 131 
#define  SSD_KEY_HARDWARE_ERROR 130 
#define  SSD_KEY_NOT_READY 129 
#define  SSD_KEY_UNIT_ATTENTION 128 
 int /*<<< orphan*/  TPC_ERR_FAIL ; 
 int /*<<< orphan*/  TPC_ERR_NO_DECREMENT ; 
 int /*<<< orphan*/  TPC_ERR_RETRY ; 
 int /*<<< orphan*/  scsi_extract_sense_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*,int*,int*,int) ; 

__attribute__((used)) static tpc_error_action
tpc_checkcond_parse(union ctl_io *io)
{
	tpc_error_action error_action;
	int error_code, sense_key, asc, ascq;

	/*
	 * Default to retrying the command.
	 */
	error_action = TPC_ERR_RETRY;

	scsi_extract_sense_len(&io->scsiio.sense_data,
			       io->scsiio.sense_len,
			       &error_code,
			       &sense_key,
			       &asc,
			       &ascq,
			       /*show_errors*/ 1);

	switch (error_code) {
	case SSD_DEFERRED_ERROR:
	case SSD_DESC_DEFERRED_ERROR:
		error_action |= TPC_ERR_NO_DECREMENT;
		break;
	case SSD_CURRENT_ERROR:
	case SSD_DESC_CURRENT_ERROR:
	default:
		switch (sense_key) {
		case SSD_KEY_UNIT_ATTENTION:
			error_action |= TPC_ERR_NO_DECREMENT;
			break;
		case SSD_KEY_HARDWARE_ERROR:
			/*
			 * This is our generic "something bad happened"
			 * error code.  It often isn't recoverable.
			 */
			if ((asc == 0x44) && (ascq == 0x00))
				error_action = TPC_ERR_FAIL;
			break;
		case SSD_KEY_NOT_READY:
			/*
			 * If the LUN is powered down, there likely isn't
			 * much point in retrying right now.
			 */
			if ((asc == 0x04) && (ascq == 0x02))
				error_action = TPC_ERR_FAIL;
			/*
			 * If the LUN is offline, there probably isn't much
			 * point in retrying, either.
			 */
			if ((asc == 0x04) && (ascq == 0x03))
				error_action = TPC_ERR_FAIL;
			break;
		}
	}
	return (error_action);
}