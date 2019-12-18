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
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int /*<<< orphan*/  RL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  activity_stop ; 
 int /*<<< orphan*/  makefile (char*) ; 
 int /*<<< orphan*/  rump_pub_lwproc_newlwp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rump_pub_lwproc_releaselwp () ; 
 int /*<<< orphan*/  rump_sys_mkdir (char*,int) ; 
 int /*<<< orphan*/  rump_sys_rmdir (char*) ; 
 int /*<<< orphan*/  rump_sys_unlink (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int,...) ; 
 int /*<<< orphan*/  wrkpid ; 

__attribute__((used)) static void *
fs_activity(void *arg)
{
	int di, fi;
	char *prefix = arg, path[128];

	rump_pub_lwproc_newlwp(wrkpid);

	RL(rump_sys_mkdir(prefix, 0777));
	while (! activity_stop) {
		for (di = 0; di < 5; di++) {
			snprintf(path, sizeof(path), "%s/d%d", prefix, di);
			RL(rump_sys_mkdir(path, 0777));
			for (fi = 0; fi < 5; fi++) {
				snprintf(path, sizeof(path), "%s/d%d/f%d",
				    prefix, di, fi);
				makefile(path);
			}
		}
		for (di = 0; di < 5; di++) {
			for (fi = 0; fi < 5; fi++) {
				snprintf(path, sizeof(path), "%s/d%d/f%d",
				    prefix, di, fi);
				RL(rump_sys_unlink(path));
			}
			snprintf(path, sizeof(path), "%s/d%d", prefix, di);
			RL(rump_sys_rmdir(path));
		}
	}
	RL(rump_sys_rmdir(prefix));

	rump_pub_lwproc_releaselwp();

	return NULL;
}