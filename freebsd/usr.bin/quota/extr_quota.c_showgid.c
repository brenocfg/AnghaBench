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
typedef  int /*<<< orphan*/  u_long ;
struct group {char* gr_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRPQUOTA ; 
 struct group* getgrgid (int /*<<< orphan*/ ) ; 
 int showquotas (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
showgid(u_long gid)
{
	struct group *grp = getgrgid(gid);
	const char *name;

	if (grp == NULL)
		name = "(no entry)";
	else
		name = grp->gr_name;
	return(showquotas(GRPQUOTA, gid, name));
}