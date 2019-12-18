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
struct statfs {int /*<<< orphan*/  f_fstypename; } ;
struct node {int dummy; } ;

/* Variables and functions */
 int asprintf (char**,char*,char const*) ; 
 struct statfs* find_statfs (struct statfs const*,int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_debugx (char*,char*) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  mount_autofs (char*,char*,char const*,char const*) ; 
 char* node_path (struct node const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
mount_if_not_already(const struct node *n, const char *map, const char *options,
    const char *prefix, const struct statfs *mntbuf, int nitems)
{
	const struct statfs *sb;
	char *mountpoint;
	char *from;
	int ret;

	ret = asprintf(&from, "map %s", map);
	if (ret < 0)
		log_err(1, "asprintf");

	mountpoint = node_path(n);
	sb = find_statfs(mntbuf, nitems, mountpoint);
	if (sb != NULL) {
		if (strcmp(sb->f_fstypename, "autofs") != 0) {
			log_debugx("unknown filesystem mounted "
			    "on %s; mounting", mountpoint);
			/*
			 * XXX: Compare options and 'from',
			 *	and update the mount if necessary.
			 */
		} else {
			log_debugx("autofs already mounted "
			    "on %s", mountpoint);
			free(from);
			free(mountpoint);
			return;
		}
	} else {
		log_debugx("nothing mounted on %s; mounting",
		    mountpoint);
	}

	mount_autofs(from, mountpoint, options, prefix);
	free(from);
	free(mountpoint);
}