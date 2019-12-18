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
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (int,int /*<<< orphan*/ ) ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  RUMP_ETFS_BLK ; 
 int /*<<< orphan*/  SRVURL ; 
 int /*<<< orphan*/  ZFSDEV ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int ftruncate (int,int /*<<< orphan*/ ) ; 
 int open (char const*,int,int) ; 
 int rump_init () ; 
 int rump_init_server (int /*<<< orphan*/ ) ; 
 int rump_pub_etfs_register (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int
zfs_fstest_newfs(const atf_tc_t *tc, void **buf, const char *image,
	off_t size, void *fspriv)
{
	int res;
	int fd;

	/* XXX: hardcoded zfs minimum size */
	size = MAX(64*1024*1024, size);

	res = rump_init();
	if (res != 0) {
		errno = res;
		return -1;
	}

	/* create backing image, sparse file is enough */
	if ((fd = open(image, O_RDWR | O_CREAT, 0777)) == -1)
		return -1;
	if (ftruncate(fd, size) == -1) {
		close(fd);
		return -1;
	}
	close(fd);

	res = rump_pub_etfs_register(ZFSDEV, image, RUMP_ETFS_BLK);
	if (res != 0) {
		errno = res;
		return -1;
	}

	res = rump_init_server(SRVURL);
	if (res != 0) {
		errno = res;
		return -1;
	}
	*buf = NULL;

	return 0;
}