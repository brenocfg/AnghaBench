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
struct disklabel {int /*<<< orphan*/  d_packname; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 struct disklabel* getdiskbyname (char const*) ; 
 struct disklabel* getvirginlabel () ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void
makelabel(const char *type, struct disklabel *lp)
{
	struct disklabel *dp;

	if (strcmp(type, "auto") == 0)
		dp = getvirginlabel();
	else
		dp = getdiskbyname(type);
	if (dp == NULL)
		errx(1, "%s: unknown disk type", type);
	*lp = *dp;
	bzero(lp->d_packname, sizeof(lp->d_packname));
}