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
struct test {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_IO ; 
 scalar_t__ chmod (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ initialized ; 
 int /*<<< orphan*/  saved_perms ; 

void
priv_io_cleanup(int asroot, int asjail, struct test *test)
{

	if (!initialized)
		return;
	if (chmod(DEV_IO, saved_perms) < 0)
		err(-1, "priv_io_cleanup: chmod(%s, 0%o)", DEV_IO,
		    saved_perms);
	initialized = 0;
}