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
struct ata_cmd {int control; int command; int features; int sector_count_exp; int /*<<< orphan*/  lba_low; } ;

/* Variables and functions */

char *
ata_op_string(struct ata_cmd *cmd)
{

	if (cmd->control & 0x04)
		return ("SOFT_RESET");
	switch (cmd->command) {
	case 0x00:
		switch (cmd->features) {
		case 0x00: return ("NOP FLUSHQUEUE");
		case 0x01: return ("NOP AUTOPOLL");
		}
		return ("NOP");
	case 0x03: return ("CFA_REQUEST_EXTENDED_ERROR");
	case 0x06:
		switch (cmd->features) {
		case 0x01: return ("DSM TRIM");
		}
		return "DSM";
	case 0x07:
		switch (cmd->features) {
		case 0x01: return ("DSM_XL TRIM");
		}
		return "DSM_XL";
	case 0x08: return ("DEVICE_RESET");
	case 0x0b: return ("REQUEST_SENSE_DATA_EXT");
	case 0x12: return ("GET_PHYSICAL_ELEMENT_STATUS");
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
	case 0x44:
		switch (cmd->features) {
		case 0x01: return ("ZERO_EXT TRIM");
		}
		return "ZERO_EXT";
	case 0x45:
		switch (cmd->features) {
		case 0x55: return ("WRITE_UNCORRECTABLE48 PSEUDO");
		case 0xaa: return ("WRITE_UNCORRECTABLE48 FLAGGED");
		}
		return "WRITE_UNCORRECTABLE48";
	case 0x47: return ("READ_LOG_DMA_EXT");
	case 0x4a: return ("ZAC_MANAGEMENT_IN");
	case 0x51: return ("CONFIGURE_STREAM");
	case 0x57: return ("WRITE_LOG_DMA_EXT");
	case 0x5b: return ("TRUSTED_NON_DATA");
	case 0x5c: return ("TRUSTED_RECEIVE");
	case 0x5d: return ("TRUSTED_RECEIVE_DMA");
	case 0x5e: return ("TRUSTED_SEND");
	case 0x5f: return ("TRUSTED_SEND_DMA");
	case 0x60: return ("READ_FPDMA_QUEUED");
	case 0x61: return ("WRITE_FPDMA_QUEUED");
	case 0x63:
		switch (cmd->features & 0xf) {
		case 0x00: return ("NCQ_NON_DATA ABORT NCQ QUEUE");
		case 0x01: return ("NCQ_NON_DATA DEADLINE HANDLING");
		case 0x02: return ("NCQ_NON_DATA HYBRID DEMOTE BY SIZE");
		case 0x03: return ("NCQ_NON_DATA HYBRID CHANGE BY LBA RANGE");
		case 0x04: return ("NCQ_NON_DATA HYBRID CONTROL");
		case 0x05: return ("NCQ_NON_DATA SET FEATURES");
		/*
		 * XXX KDM need common decoding between NCQ and non-NCQ
		 * versions of SET FEATURES.
		 */
		case 0x06: return ("NCQ_NON_DATA ZERO EXT");
		case 0x07: return ("NCQ_NON_DATA ZAC MANAGEMENT OUT");
		}
		return ("NCQ_NON_DATA");
	case 0x64:
		switch (cmd->sector_count_exp & 0xf) {
		case 0x00: return ("SEND_FPDMA_QUEUED DATA SET MANAGEMENT");
		case 0x01: return ("SEND_FPDMA_QUEUED HYBRID EVICT");
		case 0x02: return ("SEND_FPDMA_QUEUED WRITE LOG DMA EXT");
		case 0x03: return ("SEND_FPDMA_QUEUED ZAC MANAGEMENT OUT");
		case 0x04: return ("SEND_FPDMA_QUEUED DATA SET MANAGEMENT XL");
		}
		return ("SEND_FPDMA_QUEUED");
	case 0x65:
		switch (cmd->sector_count_exp & 0xf) {
		case 0x01: return ("RECEIVE_FPDMA_QUEUED READ LOG DMA EXT");
		case 0x02: return ("RECEIVE_FPDMA_QUEUED ZAC MANAGEMENT IN");
		}
		return ("RECEIVE_FPDMA_QUEUED");
	case 0x67:
		if (cmd->features == 0xec)
			return ("SEP_ATTN IDENTIFY");
		switch (cmd->lba_low) {
		case 0x00: return ("SEP_ATTN READ BUFFER");
		case 0x02: return ("SEP_ATTN RECEIVE DIAGNOSTIC RESULTS");
		case 0x80: return ("SEP_ATTN WRITE BUFFER");
		case 0x82: return ("SEP_ATTN SEND DIAGNOSTIC");
		}
		return ("SEP_ATTN");
	case 0x70: return ("SEEK");
	case 0x77: return ("SET_DATE_TIME_EXT");
	case 0x78:
		switch (cmd->features) {
		case 0x00: return ("GET_NATIVE_MAX_ADDRESS_EXT");
		case 0x01: return ("SET_ACCESSIBLE_MAX_ADDRESS_EXT");
		case 0x02: return ("FREEZE_ACCESSIBLE_MAX_ADDRESS_EXT");
		}
		return ("ACCESSIBLE_MAX_ADDRESS_CONFIGURATION");
	case 0x7C: return ("REMOVE_ELEMENT_AND_TRUNCATE");
	case 0x87: return ("CFA_TRANSLATE_SECTOR");
	case 0x90: return ("EXECUTE_DEVICE_DIAGNOSTIC");
	case 0x92: return ("DOWNLOAD_MICROCODE");
	case 0x93: return ("DOWNLOAD_MICROCODE_DMA");
	case 0x9a: return ("ZAC_MANAGEMENT_OUT");
	case 0xa0: return ("PACKET");
	case 0xa1: return ("ATAPI_IDENTIFY");
	case 0xa2: return ("SERVICE");
	case 0xb0:
		switch(cmd->features) {
		case 0xd0: return ("SMART READ ATTR VALUES");
		case 0xd1: return ("SMART READ ATTR THRESHOLDS");
		case 0xd3: return ("SMART SAVE ATTR VALUES");
		case 0xd4: return ("SMART EXECUTE OFFLINE IMMEDIATE");
		case 0xd5: return ("SMART READ LOG");
		case 0xd6: return ("SMART WRITE LOG");
		case 0xd8: return ("SMART ENABLE OPERATION");
		case 0xd9: return ("SMART DISABLE OPERATION");
		case 0xda: return ("SMART RETURN STATUS");
		}
		return ("SMART");
	case 0xb1: return ("DEVICE CONFIGURATION");
	case 0xb2: return ("SET_SECTOR_CONFIGURATION_EXT");
	case 0xb4:
		switch(cmd->features) {
		case 0x00: return ("SANITIZE_STATUS_EXT");
		case 0x11: return ("CRYPTO_SCRAMBLE_EXT");
		case 0x12: return ("BLOCK_ERASE_EXT");
		case 0x14: return ("OVERWRITE_EXT");
		case 0x20: return ("SANITIZE_FREEZE_LOCK_EXT");
		case 0x40: return ("SANITIZE_ANTIFREEZE_LOCK_EXT");
		}
		return ("SANITIZE_DEVICE");
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
	case 0xe8: return ("WRITE_BUFFER/PM");
	case 0xe9: return ("READ_BUFFER_DMA");
	case 0xea: return ("FLUSHCACHE48");
	case 0xeb: return ("WRITE_BUFFER_DMA");
	case 0xec: return ("ATA_IDENTIFY");
	case 0xed: return ("MEDIA_EJECT");
	case 0xef:
		/*
		 * XXX KDM need common decoding between NCQ and non-NCQ
		 * versions of SET FEATURES.
		 */
		switch (cmd->features) {
	        case 0x02: return ("SETFEATURES ENABLE WCACHE");
	        case 0x03: return ("SETFEATURES SET TRANSFER MODE");
		case 0x05: return ("SETFEATURES ENABLE APM");
	        case 0x06: return ("SETFEATURES ENABLE PUIS");
	        case 0x07: return ("SETFEATURES SPIN-UP");
		case 0x0b: return ("SETFEATURES ENABLE WRITE READ VERIFY");
		case 0x0c: return ("SETFEATURES ENABLE DEVICE LIFE CONTROL");
	        case 0x10: return ("SETFEATURES ENABLE SATA FEATURE");
		case 0x41: return ("SETFEATURES ENABLE FREEFALL CONTROL");
		case 0x43: return ("SETFEATURES SET MAX HOST INT SECT TIMES");
		case 0x45: return ("SETFEATURES SET RATE BASIS");
		case 0x4a: return ("SETFEATURES EXTENDED POWER CONDITIONS");
		case 0x50: return ("SETFEATURES ADVANCED BACKGROUD OPERATION");
	        case 0x55: return ("SETFEATURES DISABLE RCACHE");
		case 0x5d: return ("SETFEATURES ENABLE RELIRQ");
		case 0x5e: return ("SETFEATURES ENABLE SRVIRQ");
		case 0x62: return ("SETFEATURES LONG PHYS SECT ALIGN ERC");
		case 0x63: return ("SETFEATURES DSN");
		case 0x66: return ("SETFEATURES DISABLE DEFAULTS");
	        case 0x82: return ("SETFEATURES DISABLE WCACHE");
	        case 0x85: return ("SETFEATURES DISABLE APM");
	        case 0x86: return ("SETFEATURES DISABLE PUIS");
		case 0x8b: return ("SETFEATURES DISABLE WRITE READ VERIFY");
		case 0x8c: return ("SETFEATURES DISABLE DEVICE LIFE CONTROL");
	        case 0x90: return ("SETFEATURES DISABLE SATA FEATURE");
	        case 0xaa: return ("SETFEATURES ENABLE RCACHE");
		case 0xC1: return ("SETFEATURES DISABLE FREEFALL CONTROL");
		case 0xC3: return ("SETFEATURES SENSE DATA REPORTING");
		case 0xC4: return ("SETFEATURES NCQ SENSE DATA RETURN");
		case 0xCC: return ("SETFEATURES ENABLE DEFAULTS");
		case 0xdd: return ("SETFEATURES DISABLE RELIRQ");
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
	return "UNKNOWN";
}