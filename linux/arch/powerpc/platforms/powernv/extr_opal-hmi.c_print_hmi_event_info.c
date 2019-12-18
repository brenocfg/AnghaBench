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
struct OpalHMIEvent {scalar_t__ version; int severity; scalar_t__ disposition; size_t type; int /*<<< orphan*/  tfmr; int /*<<< orphan*/  hmer; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const**) ; 
 char* KERN_ERR ; 
 char* KERN_INFO ; 
 char* KERN_WARNING ; 
 scalar_t__ OpalHMIEvt_V1 ; 
 scalar_t__ OpalHMIEvt_V2 ; 
 scalar_t__ OpalHMI_DISPOSITION_RECOVERED ; 
 size_t OpalHMI_ERROR_MALFUNC_ALERT ; 
 size_t OpalHMI_ERROR_TFAC ; 
 size_t OpalHMI_ERROR_TFMR_PARITY ; 
#define  OpalHMI_SEV_ERROR_SYNC 131 
#define  OpalHMI_SEV_FATAL 130 
#define  OpalHMI_SEV_NO_ERROR 129 
#define  OpalHMI_SEV_WARNING 128 
 char const* be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  print_checkstop_reason (char const*,struct OpalHMIEvent*) ; 
 int /*<<< orphan*/  printk (char*,char const*,char const*,...) ; 

__attribute__((used)) static void print_hmi_event_info(struct OpalHMIEvent *hmi_evt)
{
	const char *level, *sevstr, *error_info;
	static const char *hmi_error_types[] = {
		"Malfunction Alert",
		"Processor Recovery done",
		"Processor recovery occurred again",
		"Processor recovery occurred for masked error",
		"Timer facility experienced an error",
		"TFMR SPR is corrupted",
		"UPS (Uninterrupted Power System) Overflow indication",
		"An XSCOM operation failure",
		"An XSCOM operation completed",
		"SCOM has set a reserved FIR bit to cause recovery",
		"Debug trigger has set a reserved FIR bit to cause recovery",
		"A hypervisor resource error occurred",
		"CAPP recovery process is in progress",
	};

	/* Print things out */
	if (hmi_evt->version < OpalHMIEvt_V1) {
		pr_err("HMI Interrupt, Unknown event version %d !\n",
			hmi_evt->version);
		return;
	}
	switch (hmi_evt->severity) {
	case OpalHMI_SEV_NO_ERROR:
		level = KERN_INFO;
		sevstr = "Harmless";
		break;
	case OpalHMI_SEV_WARNING:
		level = KERN_WARNING;
		sevstr = "";
		break;
	case OpalHMI_SEV_ERROR_SYNC:
		level = KERN_ERR;
		sevstr = "Severe";
		break;
	case OpalHMI_SEV_FATAL:
	default:
		level = KERN_ERR;
		sevstr = "Fatal";
		break;
	}

	printk("%s%s Hypervisor Maintenance interrupt [%s]\n",
		level, sevstr,
		hmi_evt->disposition == OpalHMI_DISPOSITION_RECOVERED ?
		"Recovered" : "Not recovered");
	error_info = hmi_evt->type < ARRAY_SIZE(hmi_error_types) ?
			hmi_error_types[hmi_evt->type]
			: "Unknown";
	printk("%s Error detail: %s\n", level, error_info);
	printk("%s	HMER: %016llx\n", level, be64_to_cpu(hmi_evt->hmer));
	if ((hmi_evt->type == OpalHMI_ERROR_TFAC) ||
		(hmi_evt->type == OpalHMI_ERROR_TFMR_PARITY))
		printk("%s	TFMR: %016llx\n", level,
						be64_to_cpu(hmi_evt->tfmr));

	if (hmi_evt->version < OpalHMIEvt_V2)
		return;

	/* OpalHMIEvt_V2 and above provides reason for malfunction alert. */
	if (hmi_evt->type == OpalHMI_ERROR_MALFUNC_ALERT)
		print_checkstop_reason(level, hmi_evt);
}