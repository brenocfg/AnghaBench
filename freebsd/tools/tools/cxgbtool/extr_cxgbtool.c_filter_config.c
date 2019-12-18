#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_4__ {void* vlan_prio; void* vlan; void* dport; void* sport; int /*<<< orphan*/  dip; int /*<<< orphan*/  sip; } ;
struct TYPE_3__ {void* vlan_prio; void* vlan; void* dport; void* sport; int /*<<< orphan*/  dip; int /*<<< orphan*/  sip; } ;
struct ch_filter {int mac_addr_idx; int rss; void* filter_id; int mac_hit; int proto; int pass; void* qset; TYPE_2__ mask; TYPE_1__ val; } ;
typedef  int /*<<< orphan*/  op ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_DEL_FILTER ; 
 int /*<<< orphan*/  CHELSIO_SET_FILTER ; 
 scalar_t__ EBUSY ; 
 scalar_t__ doit (char const*,int /*<<< orphan*/ ,struct ch_filter*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,char*,...) ; 
 int get_int_arg (char*,void**) ; 
 int /*<<< orphan*/  memset (struct ch_filter*,int /*<<< orphan*/ ,int) ; 
 int parse_ipaddr (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int parse_val_mask_param (char*,void**,void**,int) ; 
 int /*<<< orphan*/  show_filters (char const*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
filter_config(int argc, char *argv[], int start_arg, const char *iff_name)
{
	int ret = 0;
	uint32_t val, mask;
	struct ch_filter op;

	if (argc < start_arg + 1)
		return -1;

	memset(&op, 0, sizeof(op));
	op.mac_addr_idx = 0xffff;
	op.rss = 1;

	if (argc == start_arg + 1 && !strcmp(argv[start_arg], "list")) {
		show_filters(iff_name);
		return 0;
	}

	if (get_int_arg(argv[start_arg++], &op.filter_id))
		return -1;
	if (argc == start_arg + 1 && (!strcmp(argv[start_arg], "delete") ||
				      !strcmp(argv[start_arg], "clear"))) {
		if (doit(iff_name, CHELSIO_DEL_FILTER, &op) < 0) {
			if (errno == EBUSY)
				err(1, "no filter support when offload in use");
			err(1, "delete filter");
		}
		return 0;
	}

	while (start_arg + 2 <= argc) {
		if (!strcmp(argv[start_arg], "sip")) {
			ret = parse_ipaddr(argv[start_arg + 1], &op.val.sip,
					   &op.mask.sip);
		} else if (!strcmp(argv[start_arg], "dip")) {
			ret = parse_ipaddr(argv[start_arg + 1], &op.val.dip,
					   &op.mask.dip);
		} else if (!strcmp(argv[start_arg], "sport")) {
			ret = parse_val_mask_param(argv[start_arg + 1],
						   &val, &mask, 0xffff);
			op.val.sport = val;
			op.mask.sport = mask;
		} else if (!strcmp(argv[start_arg], "dport")) {
			ret = parse_val_mask_param(argv[start_arg + 1],
						   &val, &mask, 0xffff);
			op.val.dport = val;
			op.mask.dport = mask;
		} else if (!strcmp(argv[start_arg], "vlan")) {
			ret = parse_val_mask_param(argv[start_arg + 1],
						   &val, &mask, 0xfff);
			op.val.vlan = val;
			op.mask.vlan = mask;
		} else if (!strcmp(argv[start_arg], "prio")) {
			ret = parse_val_mask_param(argv[start_arg + 1],
						   &val, &mask, 7);
			op.val.vlan_prio = val;
			op.mask.vlan_prio = mask;
		} else if (!strcmp(argv[start_arg], "mac")) {
			if (!strcmp(argv[start_arg + 1], "none"))
				val = -1;
			else
				ret = get_int_arg(argv[start_arg + 1], &val);
			op.mac_hit = val != (uint32_t)-1;
			op.mac_addr_idx = op.mac_hit ? val : 0;
		} else if (!strcmp(argv[start_arg], "type")) {
			if (!strcmp(argv[start_arg + 1], "tcp"))
				op.proto = 1;
			else if (!strcmp(argv[start_arg + 1], "udp"))
				op.proto = 2;
			else if (!strcmp(argv[start_arg + 1], "frag"))
				op.proto = 3;
			else
				errx(1, "unknown type \"%s\"; must be one of "
				     "\"tcp\", \"udp\", or \"frag\"",
				     argv[start_arg + 1]);
		} else if (!strcmp(argv[start_arg], "queue")) {
			ret = get_int_arg(argv[start_arg + 1], &val);
			op.qset = val;
			op.rss = 0;
		} else if (!strcmp(argv[start_arg], "action")) {
			if (!strcmp(argv[start_arg + 1], "pass"))
				op.pass = 1;
			else if (strcmp(argv[start_arg + 1], "drop"))
				errx(1, "unknown action \"%s\"; must be one of "
				     "\"pass\" or \"drop\"",
				     argv[start_arg + 1]);
		} else
 			errx(1, "unknown filter parameter \"%s\"\n"
			     "known parameters are \"mac\", \"sip\", "
			     "\"dip\", \"sport\", \"dport\", \"vlan\", "
			     "\"prio\", \"type\", \"queue\", and \"action\"",
			     argv[start_arg]);
		if (ret < 0)
			errx(1, "bad value \"%s\" for parameter \"%s\"",
			     argv[start_arg + 1], argv[start_arg]);
		start_arg += 2;
	}
	if (start_arg != argc)
		errx(1, "no value for \"%s\"", argv[start_arg]);

	if (doit(iff_name, CHELSIO_SET_FILTER, &op) < 0) {
		if (errno == EBUSY)
			err(1, "no filter support when offload in use");
		err(1, "set filter");
	}
	
	return 0;
}