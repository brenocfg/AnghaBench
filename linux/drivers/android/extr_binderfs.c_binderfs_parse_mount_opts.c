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
typedef  int /*<<< orphan*/  substring_t ;
struct binderfs_mount_opts {int max; int /*<<< orphan*/  stats_mode; } ;

/* Variables and functions */
 int BINDERFS_MAX_MINOR ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int MAX_OPT_ARGS ; 
#define  Opt_max 129 
#define  Opt_stats_mode 128 
 int /*<<< orphan*/  STATS_GLOBAL ; 
 int /*<<< orphan*/  STATS_NONE ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  match_int (int /*<<< orphan*/ *,int*) ; 
 char* match_strdup (int /*<<< orphan*/ *) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  tokens ; 

__attribute__((used)) static int binderfs_parse_mount_opts(char *data,
				     struct binderfs_mount_opts *opts)
{
	char *p, *stats;
	opts->max = BINDERFS_MAX_MINOR;
	opts->stats_mode = STATS_NONE;

	while ((p = strsep(&data, ",")) != NULL) {
		substring_t args[MAX_OPT_ARGS];
		int token;
		int max_devices;

		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_max:
			if (match_int(&args[0], &max_devices) ||
			    (max_devices < 0 ||
			     (max_devices > BINDERFS_MAX_MINOR)))
				return -EINVAL;

			opts->max = max_devices;
			break;
		case Opt_stats_mode:
			if (!capable(CAP_SYS_ADMIN))
				return -EINVAL;

			stats = match_strdup(&args[0]);
			if (!stats)
				return -ENOMEM;

			if (strcmp(stats, "global") != 0) {
				kfree(stats);
				return -EINVAL;
			}

			opts->stats_mode = STATS_GLOBAL;
			kfree(stats);
			break;
		default:
			pr_err("Invalid mount options\n");
			return -EINVAL;
		}
	}

	return 0;
}