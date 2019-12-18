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
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  S_IRWXU ; 
 int /*<<< orphan*/  dir_target ; 
 scalar_t__ mkdir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int target ; 

int
init_target(void)
{
	if (mkdir(dir_target, S_IRWXU) < 0) {
		return -1;
	}
	target = open(dir_target, O_RDONLY, 0);
	return target;
}