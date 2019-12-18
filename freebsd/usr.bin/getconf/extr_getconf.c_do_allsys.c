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
 int /*<<< orphan*/  do_onestr ; 
 int /*<<< orphan*/  do_onesys ; 
 int /*<<< orphan*/  foreach_confstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  foreach_sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_allsys(void)
{

	foreach_confstr(do_onestr);
	foreach_sysconf(do_onesys);
}