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
struct ibdiag_opt {int dummy; } ;
typedef  int /*<<< orphan*/  str_opts ;

/* Variables and functions */
 int /*<<< orphan*/  IBDIAG_CONFIG_GENERAL ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int getopt_long (int,char* const*,char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibdiag_show_usage () ; 
 scalar_t__ long_opts ; 
 scalar_t__ make_long_opts (char const*,struct ibdiag_opt const*,struct ibdiag_opt**) ; 
 int /*<<< orphan*/  make_str_opts (scalar_t__,char*,int) ; 
 char* optarg ; 
 struct ibdiag_opt** opts_map ; 
 scalar_t__ process_opt (int,char*) ; 
 char const* prog_args ; 
 char const** prog_examples ; 
 char* prog_name ; 
 int /*<<< orphan*/  read_ibdiag_config (int /*<<< orphan*/ ) ; 

int ibdiag_process_opts(int argc, char *const argv[], void *cxt,
			const char *exclude_common_str,
			const struct ibdiag_opt custom_opts[],
			int (*custom_handler) (void *cxt, int val,
					       char *optarg),
			const char *usage_args, const char *usage_examples[])
{
	char str_opts[1024];
	const struct ibdiag_opt *o;

	prog_name = argv[0];
	prog_args = usage_args;
	prog_examples = usage_examples;

	if (long_opts)
		free(long_opts);

	long_opts = make_long_opts(exclude_common_str, custom_opts, opts_map);
	if (!long_opts)
		return -1;

	read_ibdiag_config(IBDIAG_CONFIG_GENERAL);

	make_str_opts(long_opts, str_opts, sizeof(str_opts));

	while (1) {
		int ch = getopt_long(argc, argv, str_opts, long_opts, NULL);
		if (ch == -1)
			break;
		o = opts_map[ch];
		if (!o)
			ibdiag_show_usage();
		if (custom_handler) {
			if (custom_handler(cxt, ch, optarg) &&
			    process_opt(ch, optarg))
				ibdiag_show_usage();
		} else if (process_opt(ch, optarg))
			ibdiag_show_usage();
	}

	return 0;
}