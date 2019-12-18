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
struct pfctl {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCSETDEBUG ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
pfctl_load_debug(struct pfctl *pf, unsigned int level)
{
	if (ioctl(pf->dev, DIOCSETDEBUG, &level)) {
		warnx("DIOCSETDEBUG");
		return (1);
	}
	return (0);
}