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
struct pfioc_iface {int /*<<< orphan*/  pfiio_flags; } ;
typedef  int /*<<< orphan*/  pi ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCCLRIFFLAG ; 
 int /*<<< orphan*/  PFI_IFLAG_SKIP ; 
 int PF_OPT_NOACTION ; 
 int PF_OPT_QUIET ; 
 int /*<<< orphan*/  bzero (struct pfioc_iface*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct pfioc_iface*) ; 
 int /*<<< orphan*/  stderr ; 

int
pfctl_clear_interface_flags(int dev, int opts)
{
	struct pfioc_iface	pi;

	if ((opts & PF_OPT_NOACTION) == 0) {
		bzero(&pi, sizeof(pi));
		pi.pfiio_flags = PFI_IFLAG_SKIP;

		if (ioctl(dev, DIOCCLRIFFLAG, &pi))
			err(1, "DIOCCLRIFFLAG");
		if ((opts & PF_OPT_QUIET) == 0)
			fprintf(stderr, "pf: interface flags reset\n");
	}
	return (0);
}