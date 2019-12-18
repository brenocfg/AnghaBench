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
struct ibnd_config {int /*<<< orphan*/  max_smps; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_PC_ERR_SWITCH_REL_F ; 
 int /*<<< orphan*/  PRINT_CA ; 
 int /*<<< orphan*/  PRINT_ROUTER ; 
 int /*<<< orphan*/  PRINT_SWITCH ; 
 int /*<<< orphan*/  add_suppressed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calculate_suppressed_fields (char*) ; 
 int clear_counts ; 
 int clear_errors ; 
 int /*<<< orphan*/  data_counters ; 
 int data_counters_only ; 
 int details ; 
 void* dr_path ; 
 void* load_cache_file ; 
 void* node_name_map_file ; 
 int /*<<< orphan*/  node_type_to_print ; 
 int /*<<< orphan*/  obtain_sl ; 
 int /*<<< orphan*/  port_config ; 
 int /*<<< orphan*/  port_guid ; 
 char* port_guid_str ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoull (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* threshold_file ; 

__attribute__((used)) static int process_opt(void *context, int ch, char *optarg)
{
	struct ibnd_config *cfg = context;
	switch (ch) {
	case 's':
		calculate_suppressed_fields(optarg);
		break;
	case 'c':
		/* Right now this is the only "common" error */
		add_suppressed(IB_PC_ERR_SWITCH_REL_F);
		break;
	case 1:
		node_name_map_file = strdup(optarg);
		break;
	case 2:
		data_counters++;
		break;
	case 3:
		node_type_to_print |= PRINT_SWITCH;
		break;
	case 4:
		node_type_to_print |= PRINT_CA;
		break;
	case 5:
		node_type_to_print |= PRINT_ROUTER;
		break;
	case 6:
		details = 1;
		break;
	case 7:
		load_cache_file = strdup(optarg);
		break;
	case 8:
		threshold_file = strdup(optarg);
		break;
	case 9:
		data_counters_only = 1;
		break;
	case 10:
		obtain_sl = 0;
		break;
	case 'G':
	case 'S':
		port_guid_str = optarg;
		port_guid = strtoull(optarg, 0, 0);
		break;
	case 'D':
		dr_path = strdup(optarg);
		break;
	case 'r':
		port_config++;
		break;
	case 'R':		/* nop */
		break;
	case 'k':
		clear_errors = 1;
		break;
	case 'K':
		clear_counts = 1;
		break;
	case 'o':
		cfg->max_smps = strtoul(optarg, NULL, 0);
		break;
	default:
		return -1;
	}

	return 0;
}