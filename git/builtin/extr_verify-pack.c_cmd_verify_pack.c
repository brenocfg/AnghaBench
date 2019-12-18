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
 struct option const OPT_BIT (char,char*,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct option const OPT_END () ; 
 int /*<<< orphan*/  VERIFY_PACK_STAT_ONLY ; 
 int /*<<< orphan*/  VERIFY_PACK_VERBOSE ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_default_config ; 
 int parse_options (int,char const**,char const*,struct option const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option const*) ; 
 scalar_t__ verify_one_pack (char const*,unsigned int) ; 
 int /*<<< orphan*/  verify_pack_usage ; 

int cmd_verify_pack(int argc, const char **argv, const char *prefix)
{
	int err = 0;
	unsigned int flags = 0;
	int i;
	const struct option verify_pack_options[] = {
		OPT_BIT('v', "verbose", &flags, N_("verbose"),
			VERIFY_PACK_VERBOSE),
		OPT_BIT('s', "stat-only", &flags, N_("show statistics only"),
			VERIFY_PACK_STAT_ONLY),
		OPT_END()
	};

	git_config(git_default_config, NULL);
	argc = parse_options(argc, argv, prefix, verify_pack_options,
			     verify_pack_usage, 0);
	if (argc < 1)
		usage_with_options(verify_pack_usage, verify_pack_options);
	for (i = 0; i < argc; i++) {
		if (verify_one_pack(argv[i], flags))
			err = 1;
	}

	return err;
}