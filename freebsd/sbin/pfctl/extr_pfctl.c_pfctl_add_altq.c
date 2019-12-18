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
struct pfctl {int opts; TYPE_1__* paltq; int /*<<< orphan*/  dev; } ;
struct pf_altq {int /*<<< orphan*/  ifname; } ;
struct TYPE_2__ {int /*<<< orphan*/  altq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCADDALTQ ; 
 scalar_t__ ENODEV ; 
 scalar_t__ ENXIO ; 
 int PFCTL_FLAG_ALTQ ; 
 int PF_OPT_NOACTION ; 
 scalar_t__ altqsupport ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int loadopt ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct pf_altq*,int) ; 
 int /*<<< orphan*/  pfaltq_store (int /*<<< orphan*/ *) ; 

int
pfctl_add_altq(struct pfctl *pf, struct pf_altq *a)
{
	if (altqsupport &&
	    (loadopt & PFCTL_FLAG_ALTQ) != 0) {
		memcpy(&pf->paltq->altq, a, sizeof(struct pf_altq));
		if ((pf->opts & PF_OPT_NOACTION) == 0) {
			if (ioctl(pf->dev, DIOCADDALTQ, pf->paltq)) {
				if (errno == ENXIO)
					errx(1, "qtype not configured");
				else if (errno == ENODEV)
					errx(1, "%s: driver does not support "
					    "altq", a->ifname);
				else
					err(1, "DIOCADDALTQ");
			}
		}
		pfaltq_store(&pf->paltq->altq);
	}
	return (0);
}