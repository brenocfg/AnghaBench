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
struct blk_cmd_filter {int /*<<< orphan*/  write_ok; int /*<<< orphan*/  read_ok; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERASE ; 
 int /*<<< orphan*/  GPCMD_BLANK ; 
 int /*<<< orphan*/  GPCMD_CLOSE_TRACK ; 
 int /*<<< orphan*/  GPCMD_FLUSH_CACHE ; 
 int /*<<< orphan*/  GPCMD_FORMAT_UNIT ; 
 int /*<<< orphan*/  GPCMD_GET_CONFIGURATION ; 
 int /*<<< orphan*/  GPCMD_GET_EVENT_STATUS_NOTIFICATION ; 
 int /*<<< orphan*/  GPCMD_GET_PERFORMANCE ; 
 int /*<<< orphan*/  GPCMD_LOAD_UNLOAD ; 
 int /*<<< orphan*/  GPCMD_MODE_SELECT_10 ; 
 int /*<<< orphan*/  GPCMD_PAUSE_RESUME ; 
 int /*<<< orphan*/  GPCMD_PLAY_AUDIO_10 ; 
 int /*<<< orphan*/  GPCMD_PLAY_AUDIO_MSF ; 
 int /*<<< orphan*/  GPCMD_PLAY_AUDIO_TI ; 
 int /*<<< orphan*/  GPCMD_PLAY_CD ; 
 int /*<<< orphan*/  GPCMD_PREVENT_ALLOW_MEDIUM_REMOVAL ; 
 int /*<<< orphan*/  GPCMD_READ_BUFFER_CAPACITY ; 
 int /*<<< orphan*/  GPCMD_READ_CD ; 
 int /*<<< orphan*/  GPCMD_READ_CDVD_CAPACITY ; 
 int /*<<< orphan*/  GPCMD_READ_CD_MSF ; 
 int /*<<< orphan*/  GPCMD_READ_DISC_INFO ; 
 int /*<<< orphan*/  GPCMD_READ_DVD_STRUCTURE ; 
 int /*<<< orphan*/  GPCMD_READ_FORMAT_CAPACITIES ; 
 int /*<<< orphan*/  GPCMD_READ_HEADER ; 
 int /*<<< orphan*/  GPCMD_READ_SUBCHANNEL ; 
 int /*<<< orphan*/  GPCMD_READ_TOC_PMA_ATIP ; 
 int /*<<< orphan*/  GPCMD_READ_TRACK_RZONE_INFO ; 
 int /*<<< orphan*/  GPCMD_REPAIR_RZONE_TRACK ; 
 int /*<<< orphan*/  GPCMD_REPORT_KEY ; 
 int /*<<< orphan*/  GPCMD_RESERVE_RZONE_TRACK ; 
 int /*<<< orphan*/  GPCMD_SCAN ; 
 int /*<<< orphan*/  GPCMD_SEEK ; 
 int /*<<< orphan*/  GPCMD_SEND_CUE_SHEET ; 
 int /*<<< orphan*/  GPCMD_SEND_DVD_STRUCTURE ; 
 int /*<<< orphan*/  GPCMD_SEND_EVENT ; 
 int /*<<< orphan*/  GPCMD_SEND_KEY ; 
 int /*<<< orphan*/  GPCMD_SEND_OPC ; 
 int /*<<< orphan*/  GPCMD_SET_READ_AHEAD ; 
 int /*<<< orphan*/  GPCMD_SET_SPEED ; 
 int /*<<< orphan*/  GPCMD_SET_STREAMING ; 
 int /*<<< orphan*/  GPCMD_STOP_PLAY_SCAN ; 
 int /*<<< orphan*/  GPCMD_VERIFY_10 ; 
 int /*<<< orphan*/  INQUIRY ; 
 int /*<<< orphan*/  LOG_SELECT ; 
 int /*<<< orphan*/  LOG_SENSE ; 
 int /*<<< orphan*/  MAINTENANCE_IN ; 
 int /*<<< orphan*/  MODE_SELECT ; 
 int /*<<< orphan*/  MODE_SENSE ; 
 int /*<<< orphan*/  MODE_SENSE_10 ; 
 int /*<<< orphan*/  READ_10 ; 
 int /*<<< orphan*/  READ_12 ; 
 int /*<<< orphan*/  READ_16 ; 
 int /*<<< orphan*/  READ_6 ; 
 int /*<<< orphan*/  READ_BUFFER ; 
 int /*<<< orphan*/  READ_CAPACITY ; 
 int /*<<< orphan*/  READ_DEFECT_DATA ; 
 int /*<<< orphan*/  READ_LONG ; 
 int /*<<< orphan*/  RECEIVE_DIAGNOSTIC ; 
 int /*<<< orphan*/  REPORT_LUNS ; 
 int /*<<< orphan*/  REQUEST_SENSE ; 
 int /*<<< orphan*/  SERVICE_ACTION_IN_16 ; 
 int /*<<< orphan*/  START_STOP ; 
 int /*<<< orphan*/  TEST_UNIT_READY ; 
 int /*<<< orphan*/  VERIFY_16 ; 
 int /*<<< orphan*/  WRITE_10 ; 
 int /*<<< orphan*/  WRITE_12 ; 
 int /*<<< orphan*/  WRITE_16 ; 
 int /*<<< orphan*/  WRITE_6 ; 
 int /*<<< orphan*/  WRITE_LONG ; 
 int /*<<< orphan*/  WRITE_LONG_2 ; 
 int /*<<< orphan*/  WRITE_SAME ; 
 int /*<<< orphan*/  WRITE_SAME_16 ; 
 int /*<<< orphan*/  WRITE_SAME_32 ; 
 int /*<<< orphan*/  WRITE_VERIFY ; 
 int /*<<< orphan*/  WRITE_VERIFY_12 ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void blk_set_cmd_filter_defaults(struct blk_cmd_filter *filter)
{
	/* Basic read-only commands */
	__set_bit(TEST_UNIT_READY, filter->read_ok);
	__set_bit(REQUEST_SENSE, filter->read_ok);
	__set_bit(READ_6, filter->read_ok);
	__set_bit(READ_10, filter->read_ok);
	__set_bit(READ_12, filter->read_ok);
	__set_bit(READ_16, filter->read_ok);
	__set_bit(READ_BUFFER, filter->read_ok);
	__set_bit(READ_DEFECT_DATA, filter->read_ok);
	__set_bit(READ_CAPACITY, filter->read_ok);
	__set_bit(READ_LONG, filter->read_ok);
	__set_bit(INQUIRY, filter->read_ok);
	__set_bit(MODE_SENSE, filter->read_ok);
	__set_bit(MODE_SENSE_10, filter->read_ok);
	__set_bit(LOG_SENSE, filter->read_ok);
	__set_bit(START_STOP, filter->read_ok);
	__set_bit(GPCMD_VERIFY_10, filter->read_ok);
	__set_bit(VERIFY_16, filter->read_ok);
	__set_bit(REPORT_LUNS, filter->read_ok);
	__set_bit(SERVICE_ACTION_IN_16, filter->read_ok);
	__set_bit(RECEIVE_DIAGNOSTIC, filter->read_ok);
	__set_bit(MAINTENANCE_IN, filter->read_ok);
	__set_bit(GPCMD_READ_BUFFER_CAPACITY, filter->read_ok);

	/* Audio CD commands */
	__set_bit(GPCMD_PLAY_CD, filter->read_ok);
	__set_bit(GPCMD_PLAY_AUDIO_10, filter->read_ok);
	__set_bit(GPCMD_PLAY_AUDIO_MSF, filter->read_ok);
	__set_bit(GPCMD_PLAY_AUDIO_TI, filter->read_ok);
	__set_bit(GPCMD_PAUSE_RESUME, filter->read_ok);

	/* CD/DVD data reading */
	__set_bit(GPCMD_READ_CD, filter->read_ok);
	__set_bit(GPCMD_READ_CD_MSF, filter->read_ok);
	__set_bit(GPCMD_READ_DISC_INFO, filter->read_ok);
	__set_bit(GPCMD_READ_CDVD_CAPACITY, filter->read_ok);
	__set_bit(GPCMD_READ_DVD_STRUCTURE, filter->read_ok);
	__set_bit(GPCMD_READ_HEADER, filter->read_ok);
	__set_bit(GPCMD_READ_TRACK_RZONE_INFO, filter->read_ok);
	__set_bit(GPCMD_READ_SUBCHANNEL, filter->read_ok);
	__set_bit(GPCMD_READ_TOC_PMA_ATIP, filter->read_ok);
	__set_bit(GPCMD_REPORT_KEY, filter->read_ok);
	__set_bit(GPCMD_SCAN, filter->read_ok);
	__set_bit(GPCMD_GET_CONFIGURATION, filter->read_ok);
	__set_bit(GPCMD_READ_FORMAT_CAPACITIES, filter->read_ok);
	__set_bit(GPCMD_GET_EVENT_STATUS_NOTIFICATION, filter->read_ok);
	__set_bit(GPCMD_GET_PERFORMANCE, filter->read_ok);
	__set_bit(GPCMD_SEEK, filter->read_ok);
	__set_bit(GPCMD_STOP_PLAY_SCAN, filter->read_ok);

	/* Basic writing commands */
	__set_bit(WRITE_6, filter->write_ok);
	__set_bit(WRITE_10, filter->write_ok);
	__set_bit(WRITE_VERIFY, filter->write_ok);
	__set_bit(WRITE_12, filter->write_ok);
	__set_bit(WRITE_VERIFY_12, filter->write_ok);
	__set_bit(WRITE_16, filter->write_ok);
	__set_bit(WRITE_LONG, filter->write_ok);
	__set_bit(WRITE_LONG_2, filter->write_ok);
	__set_bit(WRITE_SAME, filter->write_ok);
	__set_bit(WRITE_SAME_16, filter->write_ok);
	__set_bit(WRITE_SAME_32, filter->write_ok);
	__set_bit(ERASE, filter->write_ok);
	__set_bit(GPCMD_MODE_SELECT_10, filter->write_ok);
	__set_bit(MODE_SELECT, filter->write_ok);
	__set_bit(LOG_SELECT, filter->write_ok);
	__set_bit(GPCMD_BLANK, filter->write_ok);
	__set_bit(GPCMD_CLOSE_TRACK, filter->write_ok);
	__set_bit(GPCMD_FLUSH_CACHE, filter->write_ok);
	__set_bit(GPCMD_FORMAT_UNIT, filter->write_ok);
	__set_bit(GPCMD_REPAIR_RZONE_TRACK, filter->write_ok);
	__set_bit(GPCMD_RESERVE_RZONE_TRACK, filter->write_ok);
	__set_bit(GPCMD_SEND_DVD_STRUCTURE, filter->write_ok);
	__set_bit(GPCMD_SEND_EVENT, filter->write_ok);
	__set_bit(GPCMD_SEND_KEY, filter->write_ok);
	__set_bit(GPCMD_SEND_OPC, filter->write_ok);
	__set_bit(GPCMD_SEND_CUE_SHEET, filter->write_ok);
	__set_bit(GPCMD_SET_SPEED, filter->write_ok);
	__set_bit(GPCMD_PREVENT_ALLOW_MEDIUM_REMOVAL, filter->write_ok);
	__set_bit(GPCMD_LOAD_UNLOAD, filter->write_ok);
	__set_bit(GPCMD_SET_STREAMING, filter->write_ok);
	__set_bit(GPCMD_SET_READ_AHEAD, filter->write_ok);
}