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
struct pfioc_if {int /*<<< orphan*/  ifname; } ;
struct pfctl {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  pi ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCSETSTATUSIF ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pfioc_if*) ; 
 int /*<<< orphan*/  memset (struct pfioc_if*,int /*<<< orphan*/ ,int) ; 
 int strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
pfctl_load_logif(struct pfctl *pf, char *ifname)
{
	struct pfioc_if pi;

	memset(&pi, 0, sizeof(pi));
	if (ifname && strlcpy(pi.ifname, ifname,
	    sizeof(pi.ifname)) >= sizeof(pi.ifname)) {
		warnx("pfctl_load_logif: strlcpy");
		return (1);
	}
	if (ioctl(pf->dev, DIOCSETSTATUSIF, &pi)) {
		warnx("DIOCSETSTATUSIF");
		return (1);
	}
	return (0);
}