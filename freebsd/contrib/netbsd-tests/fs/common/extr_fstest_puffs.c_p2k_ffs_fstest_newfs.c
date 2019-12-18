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
 scalar_t__ EEXIST ; 
 char* __UNCONST (char const*) ; 
 int donewfs (int /*<<< orphan*/  const*,void**,char const*,int /*<<< orphan*/ ,void*,char**) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  ffs_fstest_delfs (int /*<<< orphan*/  const*,void**) ; 
 int ffs_fstest_newfs (int /*<<< orphan*/  const*,void**,char const*,int /*<<< orphan*/ ,void*) ; 
 int mkdir (char*,int) ; 
 int /*<<< orphan*/  rump_init () ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 

int
p2k_ffs_fstest_newfs(const atf_tc_t *tc, void **argp,
	const char *image, off_t size, void *fspriv)
{
	char *rumpffs_argv[5];
	int rv;

	rump_init();
	if ((rv = ffs_fstest_newfs(tc, argp, image, size, fspriv)) != 0)
		return rv;
	if (mkdir("p2kffsfake", 0777) == -1 && errno != EEXIST)
		return errno;

	setenv("P2K_NODETACH", "1", 1);
	rumpffs_argv[0] = __UNCONST("rump_ffs");
	rumpffs_argv[1] = __UNCONST(image);
	rumpffs_argv[2] = __UNCONST("p2kffsfake"); /* NOTUSED */
	rumpffs_argv[3] = NULL;

	if ((rv = donewfs(tc, argp, image, size, fspriv, rumpffs_argv)) != 0)
		ffs_fstest_delfs(tc, argp);
	return rv;
}