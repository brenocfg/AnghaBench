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
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 int /*<<< orphan*/  WDIOCPATPAT ; 
 int /*<<< orphan*/  fd ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ is_dry_run ; 

__attribute__((used)) static int
watchdog_patpat(u_int t)
{

	if (is_dry_run)
		return 0;

	return ioctl(fd, WDIOCPATPAT, &t);
}