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
struct merge_options {int verbosity; int buffer_output; int diff_rename_limit; int merge_rename_limit; int diff_detect_rename; int merge_detect_rename; int detect_directory_renames; int /*<<< orphan*/  df_conflict_file_set; int /*<<< orphan*/  obuf; scalar_t__ renormalize; struct repository* repo; } ;

/* Variables and functions */
 char* getenv (char*) ; 
 int /*<<< orphan*/  memset (struct merge_options*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  merge_recursive_config (struct merge_options*) ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_init (int /*<<< orphan*/ *,int) ; 
 int strtol (char const*,int /*<<< orphan*/ *,int) ; 

void init_merge_options(struct merge_options *o,
			struct repository *repo)
{
	const char *merge_verbosity;
	memset(o, 0, sizeof(struct merge_options));
	o->repo = repo;
	o->verbosity = 2;
	o->buffer_output = 1;
	o->diff_rename_limit = -1;
	o->merge_rename_limit = -1;
	o->renormalize = 0;
	o->diff_detect_rename = -1;
	o->merge_detect_rename = -1;
	o->detect_directory_renames = 1;
	merge_recursive_config(o);
	merge_verbosity = getenv("GIT_MERGE_VERBOSITY");
	if (merge_verbosity)
		o->verbosity = strtol(merge_verbosity, NULL, 10);
	if (o->verbosity >= 5)
		o->buffer_output = 0;
	strbuf_init(&o->obuf, 0);
	string_list_init(&o->df_conflict_file_set, 1);
}