#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct ibv_context {TYPE_1__* device; } ;
typedef  int /*<<< orphan*/  name ;
typedef  enum ibv_gid_type { ____Placeholder_ibv_gid_type } ibv_gid_type ;
typedef  int /*<<< orphan*/  buff ;
struct TYPE_2__ {int /*<<< orphan*/  ibdev_path; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ EFAULT ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOENT ; 
 scalar_t__ ENOTSUP ; 
 int IBV_GID_TYPE_IB_ROCE_V1 ; 
 int IBV_GID_TYPE_ROCE_V2 ; 
 int /*<<< orphan*/  V1_TYPE ; 
 int /*<<< orphan*/  V2_TYPE ; 
 scalar_t__ asprintf (char**,char*,int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ ibv_read_sysfs_file (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,unsigned int) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

int ibv_query_gid_type(struct ibv_context *context, uint8_t port_num,
		       unsigned int index, enum ibv_gid_type *type)
{
	char name[32];
	char buff[11];

	snprintf(name, sizeof(name), "ports/%d/gid_attrs/types/%d", port_num,
		 index);

	/* Reset errno so that we can rely on its value upon any error flow in
	 * ibv_read_sysfs_file.
	 */
	errno = 0;
	if (ibv_read_sysfs_file(context->device->ibdev_path, name, buff,
				sizeof(buff)) <= 0) {
		char *dir_path;
		DIR *dir;

		if (errno == EINVAL) {
			/* In IB, this file doesn't exist and the kernel sets
			 * errno to -EINVAL.
			 */
			*type = IBV_GID_TYPE_IB_ROCE_V1;
			return 0;
		}
		if (asprintf(&dir_path, "%s/%s/%d/%s/",
			     context->device->ibdev_path, "ports", port_num,
			     "gid_attrs") < 0)
			return -1;
		dir = opendir(dir_path);
		free(dir_path);
		if (!dir) {
			if (errno == ENOENT)
				/* Assuming that if gid_attrs doesn't exist,
				 * we have an old kernel and all GIDs are
				 * IB/RoCE v1
				 */
				*type = IBV_GID_TYPE_IB_ROCE_V1;
			else
				return -1;
		} else {
			closedir(dir);
			errno = EFAULT;
			return -1;
		}
	} else {
		if (!strcmp(buff, V1_TYPE)) {
			*type = IBV_GID_TYPE_IB_ROCE_V1;
		} else if (!strcmp(buff, V2_TYPE)) {
			*type = IBV_GID_TYPE_ROCE_V2;
		} else {
			errno = ENOTSUP;
			return -1;
		}
	}

	return 0;
}