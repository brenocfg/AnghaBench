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
typedef  int gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 

int
getgroups(int gidsetlen, gid_t *gidset)
{
	if (gidsetlen < 2) {
		errno = EINVAL;
		return -1;
	}

	gidset[0] = 100;
	gidset[1] = 0;
	return 2;
}