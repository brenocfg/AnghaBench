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
struct sysvbfstestargs {int /*<<< orphan*/  ta_imgpath; int /*<<< orphan*/  ta_devpath; } ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct sysvbfstestargs*) ; 
 int rump_pub_etfs_remove (int /*<<< orphan*/ ) ; 
 int unlink (int /*<<< orphan*/ ) ; 

int
sysvbfs_fstest_delfs(const atf_tc_t *tc, void *buf)
{
	int res;
	struct sysvbfstestargs *args = buf;

	res = rump_pub_etfs_remove(args->ta_devpath);
	if (res != 0)
		return res;

	res = unlink(args->ta_imgpath);
	if (res != 0)
		return res;

	free(args);

	return 0;
}