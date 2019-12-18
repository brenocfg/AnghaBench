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
 int MAXPATHLEN ; 
 char* __UNCONST (char*) ; 
 char* atf_tc_get_config_var (int /*<<< orphan*/  const*,char*) ; 
 int donewfs (int /*<<< orphan*/  const*,void**,char const*,int /*<<< orphan*/ ,void*,char**) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

int
puffs_fstest_newfs(const atf_tc_t *tc, void **argp,
	const char *image, off_t size, void *fspriv)
{
	char dtfs_path[MAXPATHLEN];
	char *dtfsargv[6];
	char **theargv;

	/* build dtfs exec path from atf test dir */
	sprintf(dtfs_path, "%s/../puffs/h_dtfs/h_dtfs",
	    atf_tc_get_config_var(tc, "srcdir"));

	if (fspriv) {
		theargv = fspriv;
		theargv[0] = dtfs_path;
	} else {
		dtfsargv[0] = dtfs_path;
		dtfsargv[1] = __UNCONST("-i");
		dtfsargv[2] = __UNCONST("-s");
		dtfsargv[3] = __UNCONST("dtfs");
		dtfsargv[4] = __UNCONST("fictional");
		dtfsargv[5] = NULL;

		theargv = dtfsargv;
	}

	return donewfs(tc, argp, image, size, fspriv, theargv);
}