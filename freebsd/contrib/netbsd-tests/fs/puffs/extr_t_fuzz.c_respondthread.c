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
struct puffs_req {scalar_t__ preq_rv; } ;
struct pollfd {int fd; scalar_t__ revents; int /*<<< orphan*/  events; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int PUFFS_MSG_MAXSIZE ; 
 int /*<<< orphan*/  dacv ; 
 int dafd ; 
 int /*<<< orphan*/  damtx ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rump_sys_poll (struct pollfd*,int,int) ; 
 scalar_t__ rump_sys_read (int,char*,int) ; 
 int /*<<< orphan*/  rump_sys_write (int,char*,scalar_t__) ; 

__attribute__((used)) static void *
respondthread(void *arg)
{
	char buf[PUFFS_MSG_MAXSIZE];
	struct puffs_req *preq = (void *)buf;
	struct pollfd pfd;
	ssize_t n;

	pthread_mutex_lock(&damtx);
	for (;;) {
		while (dafd == -1)
			pthread_cond_wait(&dacv, &damtx);

		while (dafd != -1) {
			pthread_mutex_unlock(&damtx);
			pfd.fd = dafd;
			pfd.events = POLLIN;
			pfd.revents = 0;
			if (rump_sys_poll(&pfd, 1, 10) == 0) {
				pthread_mutex_lock(&damtx);
				continue;
			}
			n = rump_sys_read(dafd, buf, sizeof(buf));
			if (n <= 0) {
				pthread_mutex_lock(&damtx);
				break;
			}

			/* just say it was succesful */
			preq->preq_rv = 0;
			rump_sys_write(dafd, buf, n);
			pthread_mutex_lock(&damtx);
		}
	}

	return NULL;
}