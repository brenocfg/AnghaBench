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
struct convert_driver {int /*<<< orphan*/  required; int /*<<< orphan*/  process; int /*<<< orphan*/  clean; int /*<<< orphan*/  smudge; struct convert_driver* next; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  git_config_bool (char const*,char const*) ; 
 int git_config_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 scalar_t__ parse_config_key (char const*,char*,char const**,int*,char const**) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ *,char const*,int) ; 
 struct convert_driver* user_convert ; 
 struct convert_driver** user_convert_tail ; 
 struct convert_driver* xcalloc (int,int) ; 
 int /*<<< orphan*/ * xmemdupz (char const*,int) ; 

__attribute__((used)) static int read_convert_config(const char *var, const char *value, void *cb)
{
	const char *key, *name;
	int namelen;
	struct convert_driver *drv;

	/*
	 * External conversion drivers are configured using
	 * "filter.<name>.variable".
	 */
	if (parse_config_key(var, "filter", &name, &namelen, &key) < 0 || !name)
		return 0;
	for (drv = user_convert; drv; drv = drv->next)
		if (!strncmp(drv->name, name, namelen) && !drv->name[namelen])
			break;
	if (!drv) {
		drv = xcalloc(1, sizeof(struct convert_driver));
		drv->name = xmemdupz(name, namelen);
		*user_convert_tail = drv;
		user_convert_tail = &(drv->next);
	}

	/*
	 * filter.<name>.smudge and filter.<name>.clean specifies
	 * the command line:
	 *
	 *	command-line
	 *
	 * The command-line will not be interpolated in any way.
	 */

	if (!strcmp("smudge", key))
		return git_config_string(&drv->smudge, var, value);

	if (!strcmp("clean", key))
		return git_config_string(&drv->clean, var, value);

	if (!strcmp("process", key))
		return git_config_string(&drv->process, var, value);

	if (!strcmp("required", key)) {
		drv->required = git_config_bool(var, value);
		return 0;
	}

	return 0;
}