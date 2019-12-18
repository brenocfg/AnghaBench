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
struct ifmediareq {int ifm_count; int* ifm_ulist; int /*<<< orphan*/  ifm_name; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIOCGIFMEDIA ; 
 int /*<<< orphan*/  SIOCGIFXMEDIA ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (struct ifmediareq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

struct ifmediareq *
ifmedia_getstate(int s)
{
	static struct ifmediareq *ifmr = NULL;
	int *mwords;
	int xmedia = 1;

	if (ifmr == NULL) {
		ifmr = (struct ifmediareq *)malloc(sizeof(struct ifmediareq));
		if (ifmr == NULL)
			err(1, "malloc");

		(void) memset(ifmr, 0, sizeof(struct ifmediareq));
		(void) strlcpy(ifmr->ifm_name, name,
		    sizeof(ifmr->ifm_name));

		ifmr->ifm_count = 0;
		ifmr->ifm_ulist = NULL;

		/*
		 * We must go through the motions of reading all
		 * supported media because we need to know both
		 * the current media type and the top-level type.
		 */

		if (ioctl(s, SIOCGIFXMEDIA, (caddr_t)ifmr) < 0) {
			xmedia = 0;
		}
		if (xmedia == 0 && ioctl(s, SIOCGIFMEDIA, (caddr_t)ifmr) < 0) {
			err(1, "SIOCGIFMEDIA");
		}

		if (ifmr->ifm_count == 0)
			errx(1, "%s: no media types?", name);

		mwords = (int *)malloc(ifmr->ifm_count * sizeof(int));
		if (mwords == NULL)
			err(1, "malloc");
  
		ifmr->ifm_ulist = mwords;
		if (xmedia) {
			if (ioctl(s, SIOCGIFXMEDIA, (caddr_t)ifmr) < 0)
				err(1, "SIOCGIFXMEDIA");
		} else {
			if (ioctl(s, SIOCGIFMEDIA, (caddr_t)ifmr) < 0)
				err(1, "SIOCGIFMEDIA");
		}
	}

	return ifmr;
}