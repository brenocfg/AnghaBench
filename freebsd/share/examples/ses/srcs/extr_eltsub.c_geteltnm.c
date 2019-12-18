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

/* Variables and functions */
#define  ELMTYP_ALARM 153 
#define  ELMTYP_AMMETER 152 
#define  ELMTYP_ARRAY_DEV 151 
#define  ELMTYP_COMPORT 150 
#define  ELMTYP_DEVICE 149 
#define  ELMTYP_DISPLAY 148 
#define  ELMTYP_DOORLOCK 147 
#define  ELMTYP_ENCLOSURE 146 
#define  ELMTYP_ESCC 145 
#define  ELMTYP_FAN 144 
#define  ELMTYP_INV_OP_REASON 143 
#define  ELMTYP_KEYPAD 142 
#define  ELMTYP_LANGUAGE 141 
#define  ELMTYP_NVRAM 140 
#define  ELMTYP_POWER 139 
#define  ELMTYP_SAS_CONN 138 
#define  ELMTYP_SAS_EXP 137 
#define  ELMTYP_SCC 136 
#define  ELMTYP_SCSIXVR 135 
#define  ELMTYP_SCSI_INI 134 
#define  ELMTYP_SCSI_TGT 133 
#define  ELMTYP_SUBENC 132 
#define  ELMTYP_THERM 131 
#define  ELMTYP_UNSPECIFIED 130 
#define  ELMTYP_UPS 129 
#define  ELMTYP_VOM 128 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

char *
geteltnm(int type)
{
	static char rbuf[132];

	switch (type) {
	case ELMTYP_UNSPECIFIED:
		sprintf(rbuf, "Unspecified");
		break;
	case ELMTYP_DEVICE:
		sprintf(rbuf, "Device Slot");
		break;
	case ELMTYP_POWER:
		sprintf(rbuf, "Power Supply");
		break;
	case ELMTYP_FAN:
		sprintf(rbuf, "Cooling");
		break;
	case ELMTYP_THERM:
		sprintf(rbuf, "Temperature Sensors");
		break;
	case ELMTYP_DOORLOCK:
		sprintf(rbuf, "Door Lock");
		break;
	case ELMTYP_ALARM:
		sprintf(rbuf, "Audible alarm");
		break;
	case ELMTYP_ESCC:
		sprintf(rbuf, "Enclosure Services Controller Electronics");
		break;
	case ELMTYP_SCC:
		sprintf(rbuf, "SCC Controller Electronics");
		break;
	case ELMTYP_NVRAM:
		sprintf(rbuf, "Nonvolatile Cache");
		break;
	case ELMTYP_INV_OP_REASON:
		sprintf(rbuf, "Invalid Operation Reason");
		break;
	case ELMTYP_UPS:
		sprintf(rbuf, "Uninterruptible Power Supply");
		break;
	case ELMTYP_DISPLAY:
		sprintf(rbuf, "Display");
		break;
	case ELMTYP_KEYPAD:
		sprintf(rbuf, "Key Pad Entry");
		break;
	case ELMTYP_ENCLOSURE:
		sprintf(rbuf, "Enclosure");
		break;
	case ELMTYP_SCSIXVR:
		sprintf(rbuf, "SCSI Port/Transceiver");
		break;
	case ELMTYP_LANGUAGE:
		sprintf(rbuf, "Language");
		break;
	case ELMTYP_COMPORT:
		sprintf(rbuf, "Communication Port");
		break;
	case ELMTYP_VOM:
		sprintf(rbuf, "Voltage Sensor");
		break;
	case ELMTYP_AMMETER:
		sprintf(rbuf, "Current Sensor");
		break;
	case ELMTYP_SCSI_TGT:
		sprintf(rbuf, "SCSI Target Port");
		break;
	case ELMTYP_SCSI_INI:
		sprintf(rbuf, "SCSI Initiator Port");
		break;
	case ELMTYP_SUBENC:
		sprintf(rbuf, "Simple Subenclosure");
		break;
	case ELMTYP_ARRAY_DEV:
		sprintf(rbuf, "Array Device Slot");
		break;
	case ELMTYP_SAS_EXP:
		sprintf(rbuf, "SAS Expander");
		break;
	case ELMTYP_SAS_CONN:
		sprintf(rbuf, "SAS Connector");
		break;
	default:
		(void) sprintf(rbuf, "<Type 0x%x>", type);
		break;
	}
	return (rbuf);
}