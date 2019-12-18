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
struct ch_hw_sched {unsigned int sched; int mode; int channel; int kbps; int class_ipg; int flow_ipg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_SET_HW_SCHED ; 
 scalar_t__ doit (char const*,int /*<<< orphan*/ ,struct ch_hw_sched*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 scalar_t__ get_int_arg (char*,unsigned int*) ; 
 int /*<<< orphan*/  get_sched_param (int,char**,int,unsigned int*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int
tx_sched(int argc, char *argv[], int start_arg, const char *iff_name)
{
	struct ch_hw_sched op;
	unsigned int idx, val;

	if (argc < 5 || get_int_arg(argv[start_arg++], &idx))
		return -1;

	op.sched = idx;
	op.mode = op.channel = -1;
	op.kbps = op.class_ipg = op.flow_ipg = -1;

	while (argc > start_arg) {
		if (!strcmp(argv[start_arg], "mode")) {
			if (start_arg + 1 >= argc)
				errx(1, "missing value for mode");
			if (!strcmp(argv[start_arg + 1], "class"))
				op.mode = 0;
			else if (!strcmp(argv[start_arg + 1], "flow"))
				op.mode = 1;
			else
				errx(1, "bad mode \"%s\"", argv[start_arg + 1]);
		} else if (!strcmp(argv[start_arg], "channel") &&
			 !get_sched_param(argc, argv, start_arg, &val))
			op.channel = val;
		else if (!strcmp(argv[start_arg], "rate") &&
			 !get_sched_param(argc, argv, start_arg, &val))
			op.kbps = val;
		else if (!strcmp(argv[start_arg], "ipg") &&
			 !get_sched_param(argc, argv, start_arg, &val))
			op.class_ipg = val;
		else if (!strcmp(argv[start_arg], "flowipg") &&
			 !get_sched_param(argc, argv, start_arg, &val))
			op.flow_ipg = val;
		else
			errx(1, "unknown scheduler parameter \"%s\"",
			     argv[start_arg]);
		start_arg += 2;
	}

	if (doit(iff_name, CHELSIO_SET_HW_SCHED, &op) < 0)
		 err(1, "pktsched");

	return 0;
}