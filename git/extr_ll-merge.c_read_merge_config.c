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
struct ll_merge_driver {int /*<<< orphan*/  recursive; int /*<<< orphan*/  cmdline; int /*<<< orphan*/  description; struct ll_merge_driver* next; int /*<<< orphan*/  fn; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  default_ll_merge ; 
 int error (char*,char const*) ; 
 int git_config_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  ll_ext_merge ; 
 struct ll_merge_driver* ll_user_merge ; 
 struct ll_merge_driver** ll_user_merge_tail ; 
 scalar_t__ parse_config_key (char const*,char*,char const**,int*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ *,char const*,int) ; 
 struct ll_merge_driver* xcalloc (int,int) ; 
 int /*<<< orphan*/ * xmemdupz (char const*,int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static int read_merge_config(const char *var, const char *value, void *cb)
{
	struct ll_merge_driver *fn;
	const char *key, *name;
	int namelen;

	if (!strcmp(var, "merge.default"))
		return git_config_string(&default_ll_merge, var, value);

	/*
	 * We are not interested in anything but "merge.<name>.variable";
	 * especially, we do not want to look at variables such as
	 * "merge.summary", "merge.tool", and "merge.verbosity".
	 */
	if (parse_config_key(var, "merge", &name, &namelen, &key) < 0 || !name)
		return 0;

	/*
	 * Find existing one as we might be processing merge.<name>.var2
	 * after seeing merge.<name>.var1.
	 */
	for (fn = ll_user_merge; fn; fn = fn->next)
		if (!strncmp(fn->name, name, namelen) && !fn->name[namelen])
			break;
	if (!fn) {
		fn = xcalloc(1, sizeof(struct ll_merge_driver));
		fn->name = xmemdupz(name, namelen);
		fn->fn = ll_ext_merge;
		*ll_user_merge_tail = fn;
		ll_user_merge_tail = &(fn->next);
	}

	if (!strcmp("name", key))
		return git_config_string(&fn->description, var, value);

	if (!strcmp("driver", key)) {
		if (!value)
			return error("%s: lacks value", var);
		/*
		 * merge.<name>.driver specifies the command line:
		 *
		 *	command-line
		 *
		 * The command-line will be interpolated with the following
		 * tokens and is given to the shell:
		 *
		 *    %O - temporary file name for the merge base.
		 *    %A - temporary file name for our version.
		 *    %B - temporary file name for the other branches' version.
		 *    %L - conflict marker length
		 *    %P - the original path (safely quoted for the shell)
		 *
		 * The external merge driver should write the results in the
		 * file named by %A, and signal that it has done with zero exit
		 * status.
		 */
		fn->cmdline = xstrdup(value);
		return 0;
	}

	if (!strcmp("recursive", key))
		return git_config_string(&fn->recursive, var, value);

	return 0;
}