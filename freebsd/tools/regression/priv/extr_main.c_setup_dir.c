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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 scalar_t__ chmod (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ chown (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*,char const*,...) ; 
 int /*<<< orphan*/ * mkdtemp (char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

void
setup_dir(const char *test, char *dpathp, uid_t uid, gid_t gid, mode_t mode)
{

	strcpy(dpathp, "/tmp/priv.XXXXXXXXXXX");
	if (mkdtemp(dpathp) == NULL)
		err(-1, "test %s: mkdtemp", test);

	if (chown(dpathp, uid, gid) < 0)
		err(-1, "test %s: chown(%s, %d, %d)", test, dpathp, uid,
		    gid);

	if (chmod(dpathp, mode) < 0)
		err(-1, "test %s: chmod(%s, 0%o)", test, dpathp, mode);
}