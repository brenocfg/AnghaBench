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
struct pfioc_tm {unsigned int timeout; unsigned int seconds; } ;
struct pfctl {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  pt ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCSETTIMEOUT ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pfioc_tm*) ; 
 int /*<<< orphan*/  memset (struct pfioc_tm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
pfctl_load_timeout(struct pfctl *pf, unsigned int timeout, unsigned int seconds)
{
	struct pfioc_tm pt;

	memset(&pt, 0, sizeof(pt));
	pt.timeout = timeout;
	pt.seconds = seconds;
	if (ioctl(pf->dev, DIOCSETTIMEOUT, &pt)) {
		warnx("DIOCSETTIMEOUT");
		return (1);
	}
	return (0);
}