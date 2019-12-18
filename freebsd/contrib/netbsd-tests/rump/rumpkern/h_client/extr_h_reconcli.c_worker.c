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
typedef  int /*<<< orphan*/  hostnamebuf ;

/* Variables and functions */
 int /*<<< orphan*/  __arraycount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closercv ; 
 int /*<<< orphan*/  closermtx ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  goodhostname ; 
 int /*<<< orphan*/  hostnamemib ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quit ; 
 int riseandwhine ; 
 int rump_sys___sysctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rump_sys_getpid () ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
worker(void *arg)
{
	char hostnamebuf[128];
	size_t blen;

	pthread_mutex_lock(&closermtx);
	while (!quit) {
		pthread_mutex_unlock(&closermtx);
		if (rump_sys_getpid() == -1)
			err(1, "getpid");

		blen = sizeof(hostnamebuf);
		memset(hostnamebuf, 0, sizeof(hostnamebuf));
		if (rump_sys___sysctl(hostnamemib, __arraycount(hostnamemib),
		    hostnamebuf, &blen, NULL, 0) == -1)
			err(1, "sysctl");
		if (strcmp(hostnamebuf, goodhostname) != 0)
			exit(1);
		pthread_mutex_lock(&closermtx);
		riseandwhine = 1;
		pthread_cond_signal(&closercv);
	}
	riseandwhine = 1;
	pthread_cond_signal(&closercv);
	pthread_mutex_unlock(&closermtx);

	return NULL;
}