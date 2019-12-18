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
typedef  int /*<<< orphan*/  rbuf ;

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
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

const char *
geteltnm(int type)
{
	static char rbuf[132];

	switch (type) {
	case ELMTYP_UNSPECIFIED:
		return ("Unspecified");
	case ELMTYP_DEVICE:
		return ("Device Slot");
	case ELMTYP_POWER:
		return ("Power Supply");
	case ELMTYP_FAN:
		return ("Cooling");
	case ELMTYP_THERM:
		return ("Temperature Sensors");
	case ELMTYP_DOORLOCK:
		return ("Door Lock");
	case ELMTYP_ALARM:
		return ("Audible alarm");
	case ELMTYP_ESCC:
		return ("Enclosure Services Controller Electronics");
	case ELMTYP_SCC:
		return ("SCC Controller Electronics");
	case ELMTYP_NVRAM:
		return ("Nonvolatile Cache");
	case ELMTYP_INV_OP_REASON:
		return ("Invalid Operation Reason");
	case ELMTYP_UPS:
		return ("Uninterruptible Power Supply");
	case ELMTYP_DISPLAY:
		return ("Display");
	case ELMTYP_KEYPAD:
		return ("Key Pad Entry");
	case ELMTYP_ENCLOSURE:
		return ("Enclosure");
	case ELMTYP_SCSIXVR:
		return ("SCSI Port/Transceiver");
	case ELMTYP_LANGUAGE:
		return ("Language");
	case ELMTYP_COMPORT:
		return ("Communication Port");
	case ELMTYP_VOM:
		return ("Voltage Sensor");
	case ELMTYP_AMMETER:
		return ("Current Sensor");
	case ELMTYP_SCSI_TGT:
		return ("SCSI Target Port");
	case ELMTYP_SCSI_INI:
		return ("SCSI Initiator Port");
	case ELMTYP_SUBENC:
		return ("Simple Subenclosure");
	case ELMTYP_ARRAY_DEV:
		return ("Array Device Slot");
	case ELMTYP_SAS_EXP:
		return ("SAS Expander");
	case ELMTYP_SAS_CONN:
		return ("SAS Connector");
	default:
		snprintf(rbuf, sizeof(rbuf), "<Type 0x%x>", type);
		return (rbuf);
	}
}