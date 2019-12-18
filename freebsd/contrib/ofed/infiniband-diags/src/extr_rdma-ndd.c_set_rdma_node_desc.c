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
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  dev_dir ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int PATH_MAX ; 
 char* SYS_INFINIBAND ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int set_retry_cnt ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 char* sys_dir ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ update_node_desc (char*,char const*,int) ; 

__attribute__((used)) static int set_rdma_node_desc(const char *hostname, int force)
{
	DIR *class_dir;
	struct dirent *dent;
	char dev_dir[PATH_MAX];

	snprintf(dev_dir, sizeof(dev_dir), "%s/%s", sys_dir, SYS_INFINIBAND);
	dev_dir[sizeof(dev_dir)-1] = '\0';

	class_dir = opendir(dev_dir);
	if (!class_dir) {
		syslog(LOG_INFO, "Failed to open %s", dev_dir);
		return -ENOSYS;
	}

	while ((dent = readdir(class_dir))) {
		int retry = set_retry_cnt;
		if (dent->d_name[0] == '.')
			continue;

		while (update_node_desc(dent->d_name, hostname, force) && retry > 0) {
			syslog(LOG_ERR, "retrying set Node Description on %s\n",
				dent->d_name);
			retry--;
		}
	}

	closedir(class_dir);
	return 0;
}