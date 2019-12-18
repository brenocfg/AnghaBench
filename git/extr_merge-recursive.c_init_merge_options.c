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
struct repository {int dummy; } ;
struct merge_options {int detect_renames; int rename_limit; int verbosity; int buffer_output; scalar_t__ renormalize; int /*<<< orphan*/  obuf; int /*<<< orphan*/  detect_directory_renames; struct repository* repo; } ;

/* Variables and functions */
 int /*<<< orphan*/  MERGE_DIRECTORY_RENAMES_CONFLICT ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  memset (struct merge_options*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  merge_recursive_config (struct merge_options*) ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int strtol (char const*,int /*<<< orphan*/ *,int) ; 

void init_merge_options(struct merge_options *opt,
			struct repository *repo)
{
	const char *merge_verbosity;
	memset(opt, 0, sizeof(struct merge_options));

	opt->repo = repo;

	opt->detect_renames = -1;
	opt->detect_directory_renames = MERGE_DIRECTORY_RENAMES_CONFLICT;
	opt->rename_limit = -1;

	opt->verbosity = 2;
	opt->buffer_output = 1;
	strbuf_init(&opt->obuf, 0);

	opt->renormalize = 0;

	merge_recursive_config(opt);
	merge_verbosity = getenv("GIT_MERGE_VERBOSITY");
	if (merge_verbosity)
		opt->verbosity = strtol(merge_verbosity, NULL, 10);
	if (opt->verbosity >= 5)
		opt->buffer_output = 0;
}