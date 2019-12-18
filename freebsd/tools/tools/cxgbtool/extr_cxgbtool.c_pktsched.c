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
struct ch_pktsched_params {int sched; unsigned int idx; unsigned int min; unsigned int max; unsigned int binding; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_SET_PKTSCHED ; 
 scalar_t__ doit (char const*,int /*<<< orphan*/ ,struct ch_pktsched_params*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 scalar_t__ get_int_arg (char*,unsigned int*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int tx_sched (int,char**,int,char const*) ; 

__attribute__((used)) static int
pktsched(int argc, char *argv[], int start_arg, const char *iff_name)
{
	struct ch_pktsched_params op;
	unsigned int idx, min = -1, max, binding = -1;

	if (argc < 4)
		errx(1, "no scheduler specified");

	if (!strcmp(argv[start_arg], "port")) {
		if (argc != start_arg + 4)
			return -1;
		if (get_int_arg(argv[start_arg + 1], &idx) ||
		    get_int_arg(argv[start_arg + 2], &min) ||
		    get_int_arg(argv[start_arg + 3], &max))
			return -1;
		op.sched = 0;
	} else if (!strcmp(argv[start_arg], "tunnelq")) {
		if (argc != start_arg + 4)
			return -1;
		if (get_int_arg(argv[start_arg + 1], &idx) ||
		    get_int_arg(argv[start_arg + 2], &max) ||
		    get_int_arg(argv[start_arg + 3], &binding))
			return -1;
		op.sched = 1;
	} else if (!strcmp(argv[start_arg], "tx"))
		return tx_sched(argc, argv, start_arg + 1, iff_name);
	else
		errx(1, "unknown scheduler \"%s\"; must be one of \"port\", " 
			"\"tunnelq\" or \"tx\"", argv[start_arg]);
 
	op.idx = idx;
	op.min = min;
	op.max = max;
	op.binding = binding;
	if (doit(iff_name, CHELSIO_SET_PKTSCHED, &op) < 0)
		 err(1, "pktsched");

	return 0;
}