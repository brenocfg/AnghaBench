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
struct group {int /*<<< orphan*/  gr_mem; int /*<<< orphan*/  gr_gid; int /*<<< orphan*/  gr_passwd; int /*<<< orphan*/  gr_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  grpGID ; 
 int /*<<< orphan*/  grpMems ; 
 int /*<<< orphan*/  grpName ; 
 int /*<<< orphan*/  grpPasswd ; 

__attribute__((used)) static void
build_grp(struct group *grp)
{
	grp->gr_name = grpName;
	grp->gr_passwd = grpPasswd;
	grp->gr_gid = grpGID;
	grp->gr_mem = grpMems;

	return;
}