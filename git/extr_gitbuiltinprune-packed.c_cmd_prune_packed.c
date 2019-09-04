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
struct option {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_ (char*) ; 
 struct option const OPT_BIT (char,char*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct option const OPT_END () ; 
 struct option const OPT_NEGBIT (char,char*,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PRUNE_PACKED_DRY_RUN ; 
 int PRUNE_PACKED_VERBOSE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ isatty (int) ; 
 int parse_options (int,char const**,char const*,struct option const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prune_packed_objects (int) ; 
 int /*<<< orphan*/  prune_packed_usage ; 
 int /*<<< orphan*/  usage_msg_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct option const*) ; 

int cmd_prune_packed(int argc, const char **argv, const char *prefix)
{
	int opts = isatty(2) ? PRUNE_PACKED_VERBOSE : 0;
	const struct option prune_packed_options[] = {
		OPT_BIT('n', "dry-run", &opts, N_("dry run"),
			PRUNE_PACKED_DRY_RUN),
		OPT_NEGBIT('q', "quiet", &opts, N_("be quiet"),
			   PRUNE_PACKED_VERBOSE),
		OPT_END()
	};

	argc = parse_options(argc, argv, prefix, prune_packed_options,
			     prune_packed_usage, 0);

	if (argc > 0)
		usage_msg_opt(_("too many arguments"),
			      prune_packed_usage,
			      prune_packed_options);

	prune_packed_objects(opts);
	return 0;
}