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
typedef  int /*<<< orphan*/  u_long ;
struct rt_msghdr {int /*<<< orphan*/  rtm_msglen; } ;

/* Variables and functions */
 int AF_INET6 ; 
 int CTL_NET ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int NET_RT_DUMP ; 
 int PF_ROUTE ; 
 int RT_DUMP_MAXRETRY ; 
 int /*<<< orphan*/  fatal (char*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  nitems (int*) ; 
 int /*<<< orphan*/  rt_entry (struct rt_msghdr*,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 scalar_t__ sysctl (int*,int /*<<< orphan*/ ,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
krtread(int again)
{
	int mib[6];
	size_t msize;
	char *buf, *p, *lim;
	struct rt_msghdr *rtm;
	int retry;
	const char *errmsg;

	retry = 0;
	buf = NULL;
	mib[0] = CTL_NET;
	mib[1] = PF_ROUTE;
	mib[2] = 0;
	mib[3] = AF_INET6;	/* Address family */
	mib[4] = NET_RT_DUMP;	/* Dump the kernel routing table */
	mib[5] = 0;		/* No flags */
	do {
		if (retry)
			sleep(1);
		retry++;
		errmsg = NULL;
		if (buf) {
			free(buf);
			buf = NULL;
		}
		if (sysctl(mib, nitems(mib), NULL, &msize, NULL, 0) < 0) {
			errmsg = "sysctl estimate";
			continue;
		}
		if ((buf = malloc(msize)) == NULL) {
			errmsg = "malloc";
			continue;
		}
		if (sysctl(mib, nitems(mib), buf, &msize, NULL, 0) < 0) {
			errmsg = "sysctl NET_RT_DUMP";
			continue;
		}
	} while (retry < RT_DUMP_MAXRETRY && errmsg != NULL);
	if (errmsg) {
		fatal("%s (with %d retries, msize=%lu)", errmsg, retry,
		    (u_long)msize);
		/*NOTREACHED*/
	} else if (1 < retry)
		syslog(LOG_INFO, "NET_RT_DUMP %d retires", retry);

	lim = buf + msize;
	for (p = buf; p < lim; p += rtm->rtm_msglen) {
		rtm = (struct rt_msghdr *)(void *)p;
		rt_entry(rtm, again);
	}
	free(buf);
}