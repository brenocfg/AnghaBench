#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_12__ {size_t link_error_type; scalar_t__ effective_address; int /*<<< orphan*/  effective_address_provided; } ;
struct TYPE_18__ {size_t ra_error_type; scalar_t__ effective_address; int /*<<< orphan*/  effective_address_provided; } ;
struct TYPE_17__ {size_t user_error_type; scalar_t__ effective_address; int /*<<< orphan*/  effective_address_provided; } ;
struct TYPE_16__ {size_t tlb_error_type; scalar_t__ effective_address; int /*<<< orphan*/  effective_address_provided; } ;
struct TYPE_15__ {size_t erat_error_type; scalar_t__ effective_address; int /*<<< orphan*/  effective_address_provided; } ;
struct TYPE_14__ {size_t slb_error_type; scalar_t__ effective_address; int /*<<< orphan*/  effective_address_provided; } ;
struct TYPE_13__ {size_t ue_error_type; scalar_t__ physical_address; int /*<<< orphan*/  physical_address_provided; scalar_t__ effective_address; int /*<<< orphan*/  effective_address_provided; } ;
struct TYPE_19__ {TYPE_1__ link_error; TYPE_7__ ra_error; TYPE_6__ user_error; TYPE_5__ tlb_error; TYPE_4__ erat_error; TYPE_3__ slb_error; TYPE_2__ ue_error; } ;
struct machine_check_event {scalar_t__ version; int severity; int initiator; int error_type; scalar_t__ disposition; size_t error_class; int /*<<< orphan*/  cpu; scalar_t__ srr0; TYPE_8__ u; } ;
struct TYPE_20__ {int /*<<< orphan*/  mce_faulty_slbs; } ;
struct TYPE_11__ {int /*<<< orphan*/  comm; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const**) ; 
 char* KERN_ERR ; 
 char* KERN_INFO ; 
 char* KERN_WARNING ; 
 scalar_t__ MCE_DISPOSITION_RECOVERED ; 
#define  MCE_ERROR_TYPE_DCACHE 147 
#define  MCE_ERROR_TYPE_ERAT 146 
#define  MCE_ERROR_TYPE_ICACHE 145 
#define  MCE_ERROR_TYPE_LINK 144 
#define  MCE_ERROR_TYPE_RA 143 
#define  MCE_ERROR_TYPE_SLB 142 
#define  MCE_ERROR_TYPE_TLB 141 
#define  MCE_ERROR_TYPE_UE 140 
#define  MCE_ERROR_TYPE_UNKNOWN 139 
#define  MCE_ERROR_TYPE_USER 138 
#define  MCE_INITIATOR_CPU 137 
#define  MCE_INITIATOR_ISA 136 
#define  MCE_INITIATOR_MEMORY 135 
#define  MCE_INITIATOR_PCI 134 
#define  MCE_INITIATOR_POWERMGM 133 
#define  MCE_INITIATOR_UNKNOWN 132 
#define  MCE_SEV_FATAL 131 
#define  MCE_SEV_NO_ERROR 130 
#define  MCE_SEV_SEVERE 129 
#define  MCE_SEV_WARNING 128 
 scalar_t__ MCE_V1 ; 
 TYPE_10__* current ; 
 TYPE_9__* local_paca ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,char const*,int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  slb_dump_contents (int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,scalar_t__) ; 

void machine_check_print_event_info(struct machine_check_event *evt,
				    bool user_mode, bool in_guest)
{
	const char *level, *sevstr, *subtype, *err_type, *initiator;
	uint64_t ea = 0, pa = 0;
	int n = 0;
	char dar_str[50];
	char pa_str[50];
	static const char *mc_ue_types[] = {
		"Indeterminate",
		"Instruction fetch",
		"Page table walk ifetch",
		"Load/Store",
		"Page table walk Load/Store",
	};
	static const char *mc_slb_types[] = {
		"Indeterminate",
		"Parity",
		"Multihit",
	};
	static const char *mc_erat_types[] = {
		"Indeterminate",
		"Parity",
		"Multihit",
	};
	static const char *mc_tlb_types[] = {
		"Indeterminate",
		"Parity",
		"Multihit",
	};
	static const char *mc_user_types[] = {
		"Indeterminate",
		"tlbie(l) invalid",
	};
	static const char *mc_ra_types[] = {
		"Indeterminate",
		"Instruction fetch (bad)",
		"Instruction fetch (foreign)",
		"Page table walk ifetch (bad)",
		"Page table walk ifetch (foreign)",
		"Load (bad)",
		"Store (bad)",
		"Page table walk Load/Store (bad)",
		"Page table walk Load/Store (foreign)",
		"Load/Store (foreign)",
	};
	static const char *mc_link_types[] = {
		"Indeterminate",
		"Instruction fetch (timeout)",
		"Page table walk ifetch (timeout)",
		"Load (timeout)",
		"Store (timeout)",
		"Page table walk Load/Store (timeout)",
	};
	static const char *mc_error_class[] = {
		"Unknown",
		"Hardware error",
		"Probable Hardware error (some chance of software cause)",
		"Software error",
		"Probable Software error (some chance of hardware cause)",
	};

	/* Print things out */
	if (evt->version != MCE_V1) {
		pr_err("Machine Check Exception, Unknown event version %d !\n",
		       evt->version);
		return;
	}
	switch (evt->severity) {
	case MCE_SEV_NO_ERROR:
		level = KERN_INFO;
		sevstr = "Harmless";
		break;
	case MCE_SEV_WARNING:
		level = KERN_WARNING;
		sevstr = "Warning";
		break;
	case MCE_SEV_SEVERE:
		level = KERN_ERR;
		sevstr = "Severe";
		break;
	case MCE_SEV_FATAL:
	default:
		level = KERN_ERR;
		sevstr = "Fatal";
		break;
	}

	switch(evt->initiator) {
	case MCE_INITIATOR_CPU:
		initiator = "CPU";
		break;
	case MCE_INITIATOR_PCI:
		initiator = "PCI";
		break;
	case MCE_INITIATOR_ISA:
		initiator = "ISA";
		break;
	case MCE_INITIATOR_MEMORY:
		initiator = "Memory";
		break;
	case MCE_INITIATOR_POWERMGM:
		initiator = "Power Management";
		break;
	case MCE_INITIATOR_UNKNOWN:
	default:
		initiator = "Unknown";
		break;
	}

	switch (evt->error_type) {
	case MCE_ERROR_TYPE_UE:
		err_type = "UE";
		subtype = evt->u.ue_error.ue_error_type <
			ARRAY_SIZE(mc_ue_types) ?
			mc_ue_types[evt->u.ue_error.ue_error_type]
			: "Unknown";
		if (evt->u.ue_error.effective_address_provided)
			ea = evt->u.ue_error.effective_address;
		if (evt->u.ue_error.physical_address_provided)
			pa = evt->u.ue_error.physical_address;
		break;
	case MCE_ERROR_TYPE_SLB:
		err_type = "SLB";
		subtype = evt->u.slb_error.slb_error_type <
			ARRAY_SIZE(mc_slb_types) ?
			mc_slb_types[evt->u.slb_error.slb_error_type]
			: "Unknown";
		if (evt->u.slb_error.effective_address_provided)
			ea = evt->u.slb_error.effective_address;
		break;
	case MCE_ERROR_TYPE_ERAT:
		err_type = "ERAT";
		subtype = evt->u.erat_error.erat_error_type <
			ARRAY_SIZE(mc_erat_types) ?
			mc_erat_types[evt->u.erat_error.erat_error_type]
			: "Unknown";
		if (evt->u.erat_error.effective_address_provided)
			ea = evt->u.erat_error.effective_address;
		break;
	case MCE_ERROR_TYPE_TLB:
		err_type = "TLB";
		subtype = evt->u.tlb_error.tlb_error_type <
			ARRAY_SIZE(mc_tlb_types) ?
			mc_tlb_types[evt->u.tlb_error.tlb_error_type]
			: "Unknown";
		if (evt->u.tlb_error.effective_address_provided)
			ea = evt->u.tlb_error.effective_address;
		break;
	case MCE_ERROR_TYPE_USER:
		err_type = "User";
		subtype = evt->u.user_error.user_error_type <
			ARRAY_SIZE(mc_user_types) ?
			mc_user_types[evt->u.user_error.user_error_type]
			: "Unknown";
		if (evt->u.user_error.effective_address_provided)
			ea = evt->u.user_error.effective_address;
		break;
	case MCE_ERROR_TYPE_RA:
		err_type = "Real address";
		subtype = evt->u.ra_error.ra_error_type <
			ARRAY_SIZE(mc_ra_types) ?
			mc_ra_types[evt->u.ra_error.ra_error_type]
			: "Unknown";
		if (evt->u.ra_error.effective_address_provided)
			ea = evt->u.ra_error.effective_address;
		break;
	case MCE_ERROR_TYPE_LINK:
		err_type = "Link";
		subtype = evt->u.link_error.link_error_type <
			ARRAY_SIZE(mc_link_types) ?
			mc_link_types[evt->u.link_error.link_error_type]
			: "Unknown";
		if (evt->u.link_error.effective_address_provided)
			ea = evt->u.link_error.effective_address;
		break;
	case MCE_ERROR_TYPE_DCACHE:
		err_type = "D-Cache";
		subtype = "Unknown";
		break;
	case MCE_ERROR_TYPE_ICACHE:
		err_type = "I-Cache";
		subtype = "Unknown";
		break;
	default:
	case MCE_ERROR_TYPE_UNKNOWN:
		err_type = "Unknown";
		subtype = "";
		break;
	}

	dar_str[0] = pa_str[0] = '\0';
	if (ea && evt->srr0 != ea) {
		/* Load/Store address */
		n = sprintf(dar_str, "DAR: %016llx ", ea);
		if (pa)
			sprintf(dar_str + n, "paddr: %016llx ", pa);
	} else if (pa) {
		sprintf(pa_str, " paddr: %016llx", pa);
	}

	printk("%sMCE: CPU%d: machine check (%s) %s %s %s %s[%s]\n",
		level, evt->cpu, sevstr, in_guest ? "Guest" : "Host",
		err_type, subtype, dar_str,
		evt->disposition == MCE_DISPOSITION_RECOVERED ?
		"Recovered" : "Not recovered");

	if (in_guest || user_mode) {
		printk("%sMCE: CPU%d: PID: %d Comm: %s %sNIP: [%016llx]%s\n",
			level, evt->cpu, current->pid, current->comm,
			in_guest ? "Guest " : "", evt->srr0, pa_str);
	} else {
		printk("%sMCE: CPU%d: NIP: [%016llx] %pS%s\n",
			level, evt->cpu, evt->srr0, (void *)evt->srr0, pa_str);
	}

	printk("%sMCE: CPU%d: Initiator %s\n", level, evt->cpu, initiator);

	subtype = evt->error_class < ARRAY_SIZE(mc_error_class) ?
		mc_error_class[evt->error_class] : "Unknown";
	printk("%sMCE: CPU%d: %s\n", level, evt->cpu, subtype);

#ifdef CONFIG_PPC_BOOK3S_64
	/* Display faulty slb contents for SLB errors. */
	if (evt->error_type == MCE_ERROR_TYPE_SLB)
		slb_dump_contents(local_paca->mce_faulty_slbs);
#endif
}