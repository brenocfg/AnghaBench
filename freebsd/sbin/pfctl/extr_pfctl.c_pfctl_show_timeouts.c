#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pfioc_tm {scalar_t__ timeout; int seconds; } ;
typedef  int /*<<< orphan*/  pt ;
struct TYPE_2__ {char* name; scalar_t__ timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGETTIMEOUT ; 
 scalar_t__ PFTM_ADAPTIVE_END ; 
 scalar_t__ PFTM_ADAPTIVE_START ; 
 int PF_OPT_SHOWALL ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct pfioc_tm*) ; 
 int /*<<< orphan*/  memset (struct pfioc_tm*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* pf_timeouts ; 
 int /*<<< orphan*/  pfctl_print_title (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
pfctl_show_timeouts(int dev, int opts)
{
	struct pfioc_tm pt;
	int i;

	if (opts & PF_OPT_SHOWALL)
		pfctl_print_title("TIMEOUTS:");
	memset(&pt, 0, sizeof(pt));
	for (i = 0; pf_timeouts[i].name; i++) {
		pt.timeout = pf_timeouts[i].timeout;
		if (ioctl(dev, DIOCGETTIMEOUT, &pt))
			err(1, "DIOCGETTIMEOUT");
		printf("%-20s %10d", pf_timeouts[i].name, pt.seconds);
		if (pf_timeouts[i].timeout >= PFTM_ADAPTIVE_START &&
		    pf_timeouts[i].timeout <= PFTM_ADAPTIVE_END)
			printf(" states");
		else
			printf("s");
		printf("\n");
	}
	return (0);

}