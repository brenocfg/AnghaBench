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
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  VSS_LOG (int /*<<< orphan*/ ,char*,...) ; 
 int close (int) ; 
 int errno ; 
 int g_ufs_suspend_handle ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static int
thaw(void)
{
	int error = 0;
	if (g_ufs_suspend_handle != -1) {
		error = close(g_ufs_suspend_handle);
		if (!error) {
			g_ufs_suspend_handle = -1;
			VSS_LOG(LOG_INFO, "Successfully thaw the fs\n");
		} else {
			error = errno;
			VSS_LOG(LOG_ERR, "Fail to thaw the fs: "
			    "%d %s\n", errno, strerror(errno));
		}
	} else {
		VSS_LOG(LOG_INFO, "The fs has already been thawed\n");
	}

	return (error);
}