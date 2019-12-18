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
struct TYPE_7__ {int command; int feature; int /*<<< orphan*/  lba; } ;
struct TYPE_5__ {scalar_t__ key; } ;
struct TYPE_6__ {int saved_cmd; int* ccb; TYPE_1__ sense; } ;
struct TYPE_8__ {TYPE_3__ ata; TYPE_2__ atapi; } ;
struct ata_request {int flags; TYPE_4__ u; } ;

/* Variables and functions */
 int ATA_R_ATAPI ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const char *
ata_cmd2str(struct ata_request *request)
{
	static char buffer[20];

	if (request->flags & ATA_R_ATAPI) {
		switch (request->u.atapi.sense.key ?
		    request->u.atapi.saved_cmd : request->u.atapi.ccb[0]) {
		case 0x00: return ("TEST_UNIT_READY");
		case 0x01: return ("REZERO");
		case 0x03: return ("REQUEST_SENSE");
		case 0x04: return ("FORMAT");
		case 0x08: return ("READ");
		case 0x0a: return ("WRITE");
		case 0x10: return ("WEOF");
		case 0x11: return ("SPACE");
		case 0x12: return ("INQUIRY");
		case 0x15: return ("MODE_SELECT");
		case 0x19: return ("ERASE");
		case 0x1a: return ("MODE_SENSE");
		case 0x1b: return ("START_STOP");
		case 0x1e: return ("PREVENT_ALLOW");
		case 0x23: return ("ATAPI_READ_FORMAT_CAPACITIES");
		case 0x25: return ("READ_CAPACITY");
		case 0x28: return ("READ_BIG");
		case 0x2a: return ("WRITE_BIG");
		case 0x2b: return ("LOCATE");
		case 0x34: return ("READ_POSITION");
		case 0x35: return ("SYNCHRONIZE_CACHE");
		case 0x3b: return ("WRITE_BUFFER");
		case 0x3c: return ("READ_BUFFER");
		case 0x42: return ("READ_SUBCHANNEL");
		case 0x43: return ("READ_TOC");
		case 0x45: return ("PLAY_10");
		case 0x47: return ("PLAY_MSF");
		case 0x48: return ("PLAY_TRACK");
		case 0x4b: return ("PAUSE");
		case 0x51: return ("READ_DISK_INFO");
		case 0x52: return ("READ_TRACK_INFO");
		case 0x53: return ("RESERVE_TRACK");
		case 0x54: return ("SEND_OPC_INFO");
		case 0x55: return ("MODE_SELECT_BIG");
		case 0x58: return ("REPAIR_TRACK");
		case 0x59: return ("READ_MASTER_CUE");
		case 0x5a: return ("MODE_SENSE_BIG");
		case 0x5b: return ("CLOSE_TRACK/SESSION");
		case 0x5c: return ("READ_BUFFER_CAPACITY");
		case 0x5d: return ("SEND_CUE_SHEET");
		case 0x96: return ("SERVICE_ACTION_IN");
		case 0xa1: return ("BLANK_CMD");
		case 0xa3: return ("SEND_KEY");
		case 0xa4: return ("REPORT_KEY");
		case 0xa5: return ("PLAY_12");
		case 0xa6: return ("LOAD_UNLOAD");
		case 0xad: return ("READ_DVD_STRUCTURE");
		case 0xb4: return ("PLAY_CD");
		case 0xbb: return ("SET_SPEED");
		case 0xbd: return ("MECH_STATUS");
		case 0xbe: return ("READ_CD");
		case 0xff: return ("POLL_DSC");
		}
	} else {
		switch (request->u.ata.command) {
		case 0x00:
			switch (request->u.ata.feature) {
			case 0x00: return ("NOP FLUSHQUEUE");
			case 0x01: return ("NOP AUTOPOLL");
			}
			return ("NOP");
		case 0x03: return ("CFA_REQUEST_EXTENDED_ERROR");
		case 0x06:
			switch (request->u.ata.feature) {
			case 0x01: return ("DSM TRIM");
			}
			return "DSM";
		case 0x08: return ("DEVICE_RESET");
		case 0x20: return ("READ");
		case 0x24: return ("READ48");
		case 0x25: return ("READ_DMA48");
		case 0x26: return ("READ_DMA_QUEUED48");
		case 0x27: return ("READ_NATIVE_MAX_ADDRESS48");
		case 0x29: return ("READ_MUL48");
		case 0x2a: return ("READ_STREAM_DMA48");
		case 0x2b: return ("READ_STREAM48");
		case 0x2f: return ("READ_LOG_EXT");
		case 0x30: return ("WRITE");
		case 0x34: return ("WRITE48");
		case 0x35: return ("WRITE_DMA48");
		case 0x36: return ("WRITE_DMA_QUEUED48");
		case 0x37: return ("SET_MAX_ADDRESS48");
		case 0x39: return ("WRITE_MUL48");
		case 0x3a: return ("WRITE_STREAM_DMA48");
		case 0x3b: return ("WRITE_STREAM48");
		case 0x3d: return ("WRITE_DMA_FUA48");
		case 0x3e: return ("WRITE_DMA_QUEUED_FUA48");
		case 0x3f: return ("WRITE_LOG_EXT");
		case 0x40: return ("READ_VERIFY");
		case 0x42: return ("READ_VERIFY48");
		case 0x45:
			switch (request->u.ata.feature) {
			case 0x55: return ("WRITE_UNCORRECTABLE48 PSEUDO");
			case 0xaa: return ("WRITE_UNCORRECTABLE48 FLAGGED");
			}
			return "WRITE_UNCORRECTABLE48";
		case 0x51: return ("CONFIGURE_STREAM");
		case 0x60: return ("READ_FPDMA_QUEUED");
		case 0x61: return ("WRITE_FPDMA_QUEUED");
		case 0x63: return ("NCQ_NON_DATA");
		case 0x64: return ("SEND_FPDMA_QUEUED");
		case 0x65: return ("RECEIVE_FPDMA_QUEUED");
		case 0x67:
			if (request->u.ata.feature == 0xec)
				return ("SEP_ATTN IDENTIFY");
			switch (request->u.ata.lba) {
			case 0x00: return ("SEP_ATTN READ BUFFER");
			case 0x02: return ("SEP_ATTN RECEIVE DIAGNOSTIC RESULTS");
			case 0x80: return ("SEP_ATTN WRITE BUFFER");
			case 0x82: return ("SEP_ATTN SEND DIAGNOSTIC");
			}
			return ("SEP_ATTN");
		case 0x70: return ("SEEK");
		case 0x87: return ("CFA_TRANSLATE_SECTOR");
		case 0x90: return ("EXECUTE_DEVICE_DIAGNOSTIC");
		case 0x92: return ("DOWNLOAD_MICROCODE");
		case 0xa0: return ("PACKET");
		case 0xa1: return ("ATAPI_IDENTIFY");
		case 0xa2: return ("SERVICE");
		case 0xb0:
			switch(request->u.ata.feature) {
			case 0xd0: return ("SMART READ ATTR VALUES");
			case 0xd1: return ("SMART READ ATTR THRESHOLDS");
			case 0xd3: return ("SMART SAVE ATTR VALUES");
			case 0xd4: return ("SMART EXECUTE OFFLINE IMMEDIATE");
			case 0xd5: return ("SMART READ LOG DATA");
			case 0xd8: return ("SMART ENABLE OPERATION");
			case 0xd9: return ("SMART DISABLE OPERATION");
			case 0xda: return ("SMART RETURN STATUS");
			}
			return ("SMART");
		case 0xb1: return ("DEVICE CONFIGURATION");
		case 0xc0: return ("CFA_ERASE");
		case 0xc4: return ("READ_MUL");
		case 0xc5: return ("WRITE_MUL");
		case 0xc6: return ("SET_MULTI");
		case 0xc7: return ("READ_DMA_QUEUED");
		case 0xc8: return ("READ_DMA");
		case 0xca: return ("WRITE_DMA");
		case 0xcc: return ("WRITE_DMA_QUEUED");
		case 0xcd: return ("CFA_WRITE_MULTIPLE_WITHOUT_ERASE");
		case 0xce: return ("WRITE_MUL_FUA48");
		case 0xd1: return ("CHECK_MEDIA_CARD_TYPE");
		case 0xda: return ("GET_MEDIA_STATUS");
		case 0xde: return ("MEDIA_LOCK");
		case 0xdf: return ("MEDIA_UNLOCK");
		case 0xe0: return ("STANDBY_IMMEDIATE");
		case 0xe1: return ("IDLE_IMMEDIATE");
		case 0xe2: return ("STANDBY");
		case 0xe3: return ("IDLE");
		case 0xe4: return ("READ_BUFFER/PM");
		case 0xe5: return ("CHECK_POWER_MODE");
		case 0xe6: return ("SLEEP");
		case 0xe7: return ("FLUSHCACHE");
		case 0xe8: return ("WRITE_PM");
		case 0xea: return ("FLUSHCACHE48");
		case 0xec: return ("ATA_IDENTIFY");
		case 0xed: return ("MEDIA_EJECT");
		case 0xef:
			switch (request->u.ata.feature) {
			case 0x03: return ("SETFEATURES SET TRANSFER MODE");
			case 0x02: return ("SETFEATURES ENABLE WCACHE");
			case 0x82: return ("SETFEATURES DISABLE WCACHE");
			case 0x06: return ("SETFEATURES ENABLE PUIS");
			case 0x86: return ("SETFEATURES DISABLE PUIS");
			case 0x07: return ("SETFEATURES SPIN-UP");
			case 0x10: return ("SETFEATURES ENABLE SATA FEATURE");
			case 0x90: return ("SETFEATURES DISABLE SATA FEATURE");
			case 0xaa: return ("SETFEATURES ENABLE RCACHE");
			case 0x55: return ("SETFEATURES DISABLE RCACHE");
			case 0x5d: return ("SETFEATURES ENABLE RELIRQ");
			case 0xdd: return ("SETFEATURES DISABLE RELIRQ");
			case 0x5e: return ("SETFEATURES ENABLE SRVIRQ");
			case 0xde: return ("SETFEATURES DISABLE SRVIRQ");
			}
			return "SETFEATURES";
		case 0xf1: return ("SECURITY_SET_PASSWORD");
		case 0xf2: return ("SECURITY_UNLOCK");
		case 0xf3: return ("SECURITY_ERASE_PREPARE");
		case 0xf4: return ("SECURITY_ERASE_UNIT");
		case 0xf5: return ("SECURITY_FREEZE_LOCK");
		case 0xf6: return ("SECURITY_DISABLE_PASSWORD");
		case 0xf8: return ("READ_NATIVE_MAX_ADDRESS");
		case 0xf9: return ("SET_MAX_ADDRESS");
		}
	}
	sprintf(buffer, "unknown CMD (0x%02x)", request->u.ata.command);
	return (buffer);
}