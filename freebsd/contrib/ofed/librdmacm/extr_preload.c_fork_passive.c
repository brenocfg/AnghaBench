#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_family; int /*<<< orphan*/  sin6_addr; scalar_t__ sin6_scope_id; scalar_t__ sin6_flowinfo; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sem_t ;
struct TYPE_3__ {int (* getsockname ) (int,struct sockaddr*,int*) ;int (* write ) (int,scalar_t__*,int) ;int /*<<< orphan*/  (* close ) (int) ;int /*<<< orphan*/  (* shutdown ) (int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/ * SEM_FAILED ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int S_IRWXG ; 
 int S_IRWXU ; 
 int /*<<< orphan*/  copysockopts (int,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int fd_getd (int) ; 
 int /*<<< orphan*/  fd_normal ; 
 int /*<<< orphan*/  fd_ready ; 
 int /*<<< orphan*/  fd_rsocket ; 
 int /*<<< orphan*/  fd_store (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int raccept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rbind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  rclose (int) ; 
 TYPE_1__ real ; 
 int rlisten (int,int) ; 
 int /*<<< orphan*/  rs ; 
 int /*<<< orphan*/  rsetsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int rsocket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sem_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sem_open (char*,int,int,int) ; 
 int /*<<< orphan*/  sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_rsocket_options (int) ; 
 int stub1 (int,struct sockaddr*,int*) ; 
 int stub2 (int,scalar_t__*,int) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int) ; 

__attribute__((used)) static void fork_passive(int socket)
{
	struct sockaddr_in6 sin6;
	sem_t *sem;
	int lfd, sfd, dfd, ret, param;
	socklen_t len;
	uint32_t msg;

	sfd = fd_getd(socket);

	len = sizeof sin6;
	ret = real.getsockname(sfd, (struct sockaddr *) &sin6, &len);
	if (ret)
		goto out;
	sin6.sin6_flowinfo = 0;
	sin6.sin6_scope_id = 0;
	memset(&sin6.sin6_addr, 0, sizeof sin6.sin6_addr);

	sem = sem_open("/rsocket_fork", O_CREAT | O_RDWR,
		       S_IRWXU | S_IRWXG, 1);
	if (sem == SEM_FAILED) {
		ret = -1;
		goto out;
	}

	lfd = rsocket(sin6.sin6_family, SOCK_STREAM, 0);
	if (lfd < 0) {
		ret = lfd;
		goto sclose;
	}

	param = 1;
	rsetsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &param, sizeof param);

	sem_wait(sem);
	ret = rbind(lfd, (struct sockaddr *) &sin6, sizeof sin6);
	if (ret)
		goto lclose;

	ret = rlisten(lfd, 1);
	if (ret)
		goto lclose;

	msg = 0;
	len = real.write(sfd, &msg, sizeof msg);
	if (len != sizeof msg)
		goto lclose;

	dfd = raccept(lfd, NULL, NULL);
	if (dfd < 0) {
		ret  = dfd;
		goto lclose;
	}

	set_rsocket_options(dfd);
	copysockopts(dfd, sfd, &rs, &real);
	real.shutdown(sfd, SHUT_RDWR);
	real.close(sfd);
	fd_store(socket, dfd, fd_rsocket, fd_ready);

lclose:
	rclose(lfd);
	sem_post(sem);
sclose:
	sem_close(sem);
out:
	if (ret)
		fd_store(socket, sfd, fd_normal, fd_ready);
}