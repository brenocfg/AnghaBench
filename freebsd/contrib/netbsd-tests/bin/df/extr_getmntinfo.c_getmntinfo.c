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
struct statvfs {int dummy; } ;

/* Variables and functions */
 struct statvfs* allstatvfs ; 
 int /*<<< orphan*/  setup_filer () ; 
 int /*<<< orphan*/  setup_ld0g () ; 
 int /*<<< orphan*/  setup_pr23600 () ; 
 int /*<<< orphan*/  setup_strpct () ; 
 int sfused ; 

int
getmntinfo(struct statvfs **mntbuf, int flags)
{

	setup_filer();
	setup_ld0g();
	setup_strpct();
	setup_pr23600();

	*mntbuf = allstatvfs;
	return (sfused);
}