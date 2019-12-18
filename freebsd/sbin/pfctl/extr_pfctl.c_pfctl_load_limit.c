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
struct pfioc_limit {unsigned int index; unsigned int limit; } ;
struct pfctl {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  pl ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCSETLIMIT ; 
 scalar_t__ EBUSY ; 
 scalar_t__ errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pfioc_limit*) ; 
 int /*<<< orphan*/  memset (struct pfioc_limit*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
pfctl_load_limit(struct pfctl *pf, unsigned int index, unsigned int limit)
{
	struct pfioc_limit pl;

	memset(&pl, 0, sizeof(pl));
	pl.index = index;
	pl.limit = limit;
	if (ioctl(pf->dev, DIOCSETLIMIT, &pl)) {
		if (errno == EBUSY)
			warnx("Current pool size exceeds requested hard limit");
		else
			warnx("DIOCSETLIMIT");
		return (1);
	}
	return (0);
}