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
struct TCPApc_event {size_t event_id; } ;
struct TCPAevent {int event_type; int /*<<< orphan*/  event_size; } ;

/* Variables and functions */
#define  ACTION 157 
#define  BIS_CERT 156 
#define  CMOS 155 
#define  COMPACT_HASH 154 
#define  CPU_MICROCODE 153 
#define  ESCD 152 
#define  EVENT_TAG 151 
#define  IPL 150 
#define  IPL_PARTITION_DATA 149 
#define  NONHOST_CODE 148 
#define  NONHOST_CONFIG 147 
#define  NONHOST_INFO 146 
#define  NO_ACTION 145 
#define  NVRAM 144 
#define  OPTION_ROM_CONFIG 143 
#define  OPTION_ROM_EXEC 142 
#define  OPTION_ROM_MICROCODE 141 
#define  PLATFORM_CONFIG_FLAGS 140 
#define  POST_BIOS_ROM 139 
#define  POST_CODE 138 
#define  POST_CONTENTS 137 
#define  PREBOOT 136 
#define  SCRTM_CONTENTS 135 
#define  SCRTM_VERSION 134 
#define  SEPARATOR 133 
#define  SMBIOS 132 
#define  S_CRTM_CONTENTS 131 
#define  S_CRTM_VERSION 130 
#define  TABLE_OF_DEVICES 129 
 size_t* TCPA_pcclient_strings ; 
#define  UNUSED 128 
 int /*<<< orphan*/  asprintf (char**,char*,size_t) ; 
 char* calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,struct TCPApc_event*,int /*<<< orphan*/ ) ; 
 size_t* tcpa_event_type_strings ; 

__attribute__((used)) static char *
acpi_tcpa_evname(struct TCPAevent *event)
{
	struct TCPApc_event *pc_event;
	char *eventname = NULL;

	pc_event = (struct TCPApc_event *)(event + 1);

	switch(event->event_type) {
	case PREBOOT:
	case POST_CODE:
	case UNUSED:
	case NO_ACTION:
	case SEPARATOR:
	case SCRTM_CONTENTS:
	case SCRTM_VERSION:
	case CPU_MICROCODE:
	case PLATFORM_CONFIG_FLAGS:
	case TABLE_OF_DEVICES:
	case COMPACT_HASH:
	case IPL:
	case IPL_PARTITION_DATA:
	case NONHOST_CODE:
	case NONHOST_CONFIG:
	case NONHOST_INFO:
		asprintf(&eventname, "%s",
		    tcpa_event_type_strings[event->event_type]);
		break;

	case ACTION:
		eventname = calloc(event->event_size + 1, sizeof(char));
		memcpy(eventname, pc_event, event->event_size);
		break;

	case EVENT_TAG:
		switch (pc_event->event_id) {
		case SMBIOS:
		case BIS_CERT:
		case CMOS:
		case NVRAM:
		case OPTION_ROM_EXEC:
		case OPTION_ROM_CONFIG:
		case S_CRTM_VERSION:
		case POST_BIOS_ROM:
		case ESCD:
		case OPTION_ROM_MICROCODE:
		case S_CRTM_CONTENTS:
		case POST_CONTENTS:
			asprintf(&eventname, "%s",
			    TCPA_pcclient_strings[pc_event->event_id]);
			break;

		default:
			asprintf(&eventname, "<unknown tag 0x%02x>",
			    pc_event->event_id);
			break;
		}
		break;

	default:
		asprintf(&eventname, "<unknown 0x%02x>", event->event_type);
		break;
	}

	return eventname;
}