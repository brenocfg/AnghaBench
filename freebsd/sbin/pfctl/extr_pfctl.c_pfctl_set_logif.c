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
struct pfctl {int ifname_set; int opts; int /*<<< orphan*/ * ifname; } ;

/* Variables and functions */
 int PFCTL_FLAG_OPTION ; 
 int PF_OPT_VERBOSE ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int loadopt ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/ * strdup (char*) ; 

int
pfctl_set_logif(struct pfctl *pf, char *ifname)
{

	if ((loadopt & PFCTL_FLAG_OPTION) == 0)
		return (0);

	if (!strcmp(ifname, "none")) {
		free(pf->ifname);
		pf->ifname = NULL;
	} else {
		pf->ifname = strdup(ifname);
		if (!pf->ifname)
			errx(1, "pfctl_set_logif: strdup");
	}
	pf->ifname_set = 1;

	if (pf->opts & PF_OPT_VERBOSE)
		printf("set loginterface %s\n", ifname);

	return (0);
}