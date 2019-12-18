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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  KENV_GET ; 
 int MAX_COMMAND_LEN ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ kenv (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  libzfs_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libzfs_init () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char const* const) ; 
 scalar_t__ strtoumax (char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ zpool_nextboot (int /*<<< orphan*/ *,scalar_t__,scalar_t__,char const* const) ; 

int main(int argc, const char * const *argv)
{
	char buf[32];
	libzfs_handle_t *hdl;
	uint64_t pool_guid;
	uint64_t vdev_guid;
	int zfs_fd;
	int len;

	if (argc != 2) {
		fprintf(stderr, "usage: zfsbootcfg <boot.config(5) options>\n");
		return (1);
	}

	len = strlen(argv[1]);
	if (len >= MAX_COMMAND_LEN) {
		fprintf(stderr, "options string is too long\n");
		return (1);
	}

	if (kenv(KENV_GET, "vfs.zfs.boot.primary_pool", buf, sizeof(buf)) <= 0) {
		perror("can't get vfs.zfs.boot.primary_pool");
		return (1);
	}
	pool_guid = strtoumax(buf, NULL, 10);
	if (pool_guid == 0) {
		perror("can't parse vfs.zfs.boot.primary_pool");
		return (1);
	}

	if (kenv(KENV_GET, "vfs.zfs.boot.primary_vdev", buf, sizeof(buf)) <= 0) {
		perror("can't get vfs.zfs.boot.primary_vdev");
		return (1);
	}
	vdev_guid = strtoumax(buf, NULL, 10);
	if (vdev_guid == 0) {
		perror("can't parse vfs.zfs.boot.primary_vdev");
		return (1);
	}

	if ((hdl = libzfs_init()) == NULL) {
		(void) fprintf(stderr, "internal error: failed to "
		    "initialize ZFS library\n");
		return (1);
	}

	if (zpool_nextboot(hdl, pool_guid, vdev_guid, argv[1]) != 0) {
		perror("ZFS_IOC_NEXTBOOT failed");
		libzfs_fini(hdl);
		return (1);
	}

	libzfs_fini(hdl);
	printf("zfs next boot options are successfully written\n");
	return (0);
}