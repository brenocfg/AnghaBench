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
struct group {char* gr_name; char* gr_passwd; int gr_gid; char** gr_mem; } ;

/* Variables and functions */
 int snprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static void
sdump_group(struct group *grp, char *buffer, size_t buflen)
{
	char **cp;
	int written;

	written = snprintf(buffer, buflen, "%s:%s:%d:",
		grp->gr_name, grp->gr_passwd, grp->gr_gid);
	buffer += written;
	if (written > (int)buflen)
		return;
	buflen -= written;

	if (grp->gr_mem != NULL) {
		if (*(grp->gr_mem) != NULL) {
			for (cp = grp->gr_mem; *cp; ++cp) {
				written = snprintf(buffer, buflen, "%s%s",
				    cp == grp->gr_mem ? "" : ",", *cp);
				buffer += written;
				if (written > (int)buflen)
					return;
				buflen -= written;

				if (buflen == 0)
					return;
			}
		} else
			snprintf(buffer, buflen, "nomem");
	} else
		snprintf(buffer, buflen, "(null)");
}