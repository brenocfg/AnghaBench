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
 int ENOENT ; 
 int errno ; 
 int /*<<< orphan*/  warning_errno (char*,char const*,char const*) ; 

__attribute__((used)) static int warn_if_unremovable(const char *op, const char *file, int rc)
{
	int err;
	if (!rc || errno == ENOENT)
		return 0;
	err = errno;
	warning_errno("unable to %s '%s'", op, file);
	errno = err;
	return rc;
}