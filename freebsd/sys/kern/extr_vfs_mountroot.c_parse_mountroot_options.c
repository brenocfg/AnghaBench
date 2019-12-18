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
struct mntarg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MOUNT ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 struct mntarg* mount_arg (struct mntarg*,char*,char*,int) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char const*,int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static struct mntarg *
parse_mountroot_options(struct mntarg *ma, const char *options)
{
	char *p;
	char *name, *name_arg;
	char *val, *val_arg;
	char *opts;

	if (options == NULL || options[0] == '\0')
		return (ma);

	p = opts = strdup(options, M_MOUNT);
	if (opts == NULL) {
		return (ma);
	}

	while((name = strsep(&p, ",")) != NULL) {
		if (name[0] == '\0')
			break;

		val = strchr(name, '=');
		if (val != NULL) {
			*val = '\0';
			++val;
		}
		if( strcmp(name, "rw") == 0 ||
		    strcmp(name, "noro") == 0) {
			/*
			 * The first time we mount the root file system,
			 * we need to mount 'ro', so We need to ignore
			 * 'rw' and 'noro' mount options.
			 */
			continue;
		}
		name_arg = strdup(name, M_MOUNT);
		val_arg = NULL;
		if (val != NULL)
			val_arg = strdup(val, M_MOUNT);

		ma = mount_arg(ma, name_arg, val_arg,
		    (val_arg != NULL ? -1 : 0));
	}
	free(opts, M_MOUNT);
	return (ma);
}