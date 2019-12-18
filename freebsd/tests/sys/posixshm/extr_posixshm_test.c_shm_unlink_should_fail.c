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

/* Variables and functions */
 int /*<<< orphan*/  ATF_CHECK_MSG (int,char*,...) ; 
 int errno ; 
 int shm_unlink (char const*) ; 

__attribute__((used)) static void
shm_unlink_should_fail(const char *path, int error)
{

	ATF_CHECK_MSG(shm_unlink(path) == -1, "shm_unlink didn't fail");
	ATF_CHECK_MSG(error == errno,
	    "shm_unlink didn't fail with expected errno; errno=%d; expected "
	    "errno=%d", errno, error);
}