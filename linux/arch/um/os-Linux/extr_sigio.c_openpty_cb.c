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
struct openpty_arg {int /*<<< orphan*/  err; int /*<<< orphan*/  slave; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 scalar_t__ openpty (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void openpty_cb(void *arg)
{
	struct openpty_arg *info = arg;

	info->err = 0;
	if (openpty(&info->master, &info->slave, NULL, NULL, NULL))
		info->err = -errno;
}