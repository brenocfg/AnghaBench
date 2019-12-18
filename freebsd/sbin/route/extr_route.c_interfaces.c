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
struct rt_msghdr {int /*<<< orphan*/  rtm_msglen; } ;

/* Variables and functions */
 int AF_UNSPEC ; 
 int CTL_NET ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int NET_RT_IFLIST ; 
 int PF_ROUTE ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  nitems (int*) ; 
 int /*<<< orphan*/  print_rtmsg (struct rt_msghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 scalar_t__ sysctl (int*,int /*<<< orphan*/ ,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
interfaces(void)
{
	size_t needed;
	int mib[6];
	char *buf, *lim, *next, count = 0;
	struct rt_msghdr *rtm;

retry2:
	mib[0] = CTL_NET;
	mib[1] = PF_ROUTE;
	mib[2] = 0;		/* protocol */
	mib[3] = AF_UNSPEC;
	mib[4] = NET_RT_IFLIST;
	mib[5] = 0;		/* no flags */
	if (sysctl(mib, nitems(mib), NULL, &needed, NULL, 0) < 0)
		err(EX_OSERR, "route-sysctl-estimate");
	if ((buf = malloc(needed)) == NULL)
		errx(EX_OSERR, "malloc failed");
	if (sysctl(mib, nitems(mib), buf, &needed, NULL, 0) < 0) {
		if (errno == ENOMEM && count++ < 10) {
			warnx("Routing table grew, retrying");
			sleep(1);
			free(buf);
			goto retry2;
		}
		err(EX_OSERR, "actual retrieval of interface table");
	}
	lim = buf + needed;
	for (next = buf; next < lim; next += rtm->rtm_msglen) {
		rtm = (struct rt_msghdr *)(void *)next;
		print_rtmsg(rtm, rtm->rtm_msglen);
	}
	free(buf);
}