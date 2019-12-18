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
 int shm_unlink (char const*) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

__attribute__((used)) static int
delete_one_shm(const char *path)
{
	int error, ret;

	error = shm_unlink(path);
	if (error != 0) {
		warn("unlink of %s failed", path);
		ret = 1;
	} else {
		ret = 0;
	}
	return (ret);
}