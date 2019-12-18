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
struct pfioc_iface {int pfiio_flags; int /*<<< orphan*/  pfiio_name; } ;
struct pfctl {int opts; int /*<<< orphan*/  dev; } ;
struct node_host {char* ifname; struct node_host* next; } ;
typedef  int /*<<< orphan*/  pi ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCCLRIFFLAG ; 
 int /*<<< orphan*/  DIOCSETIFFLAG ; 
 int PFCTL_FLAG_OPTION ; 
 int PF_OPT_NOACTION ; 
 int /*<<< orphan*/  bzero (struct pfioc_iface*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 struct node_host* ifa_grouplookup (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pfioc_iface*) ; 
 int loadopt ; 
 int /*<<< orphan*/  pfctl_check_skip_ifaces (char*) ; 
 int strlcpy (int /*<<< orphan*/ ,char*,int) ; 

int
pfctl_set_interface_flags(struct pfctl *pf, char *ifname, int flags, int how)
{
	struct pfioc_iface	pi;
	struct node_host	*h = NULL, *n = NULL;

	if ((loadopt & PFCTL_FLAG_OPTION) == 0)
		return (0);

	bzero(&pi, sizeof(pi));

	pi.pfiio_flags = flags;

	/* Make sure our cache matches the kernel. If we set or clear the flag
	 * for a group this applies to all members. */
	h = ifa_grouplookup(ifname, 0);
	for (n = h; n != NULL; n = n->next)
		pfctl_set_interface_flags(pf, n->ifname, flags, how);

	if (strlcpy(pi.pfiio_name, ifname, sizeof(pi.pfiio_name)) >=
	    sizeof(pi.pfiio_name))
		errx(1, "pfctl_set_interface_flags: strlcpy");

	if ((pf->opts & PF_OPT_NOACTION) == 0) {
		if (how == 0) {
			if (ioctl(pf->dev, DIOCCLRIFFLAG, &pi))
				err(1, "DIOCCLRIFFLAG");
		} else {
			if (ioctl(pf->dev, DIOCSETIFFLAG, &pi))
				err(1, "DIOCSETIFFLAG");
			pfctl_check_skip_ifaces(ifname);
		}
	}
	return (0);
}