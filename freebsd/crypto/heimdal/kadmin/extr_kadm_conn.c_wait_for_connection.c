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
typedef  scalar_t__ krb5_socket_t ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ FD_ISSET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ FD_SETSIZE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  WNOHANG ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*) ; 
 int max (int,scalar_t__) ; 
 int /*<<< orphan*/  pgrp ; 
 scalar_t__ rk_IS_SOCKET_ERROR (int) ; 
 scalar_t__ rk_SOCK_ERRNO ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ setpgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigchld ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spawn_child (int /*<<< orphan*/ ,scalar_t__*,unsigned int,unsigned int) ; 
 scalar_t__ term_flag ; 
 int /*<<< orphan*/  terminate ; 
 scalar_t__ waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wait_for_connection(krb5_context contextp,
		    krb5_socket_t *socks, unsigned int num_socks)
{
    unsigned int i;
    int e;
    fd_set orig_read_set, read_set;
    int status, max_fd = -1;

    FD_ZERO(&orig_read_set);

    for(i = 0; i < num_socks; i++) {
#ifdef FD_SETSIZE
	if (socks[i] >= FD_SETSIZE)
	    errx (1, "fd too large");
#endif
	FD_SET(socks[i], &orig_read_set);
	max_fd = max(max_fd, socks[i]);
    }

    pgrp = getpid();

    if(setpgid(0, pgrp) < 0)
	err(1, "setpgid");

    signal(SIGTERM, terminate);
    signal(SIGINT, terminate);
    signal(SIGCHLD, sigchld);

    while (term_flag == 0) {
	read_set = orig_read_set;
	e = select(max_fd + 1, &read_set, NULL, NULL, NULL);
	if(rk_IS_SOCKET_ERROR(e)) {
	    if(rk_SOCK_ERRNO != EINTR)
		krb5_warn(contextp, rk_SOCK_ERRNO, "select");
	} else if(e == 0)
	    krb5_warnx(contextp, "select returned 0");
	else {
	    for(i = 0; i < num_socks; i++) {
		if(FD_ISSET(socks[i], &read_set))
		    if(spawn_child(contextp, socks, num_socks, i) == 0)
			return;
	    }
	}
    }
    signal(SIGCHLD, SIG_IGN);

    while ((waitpid(-1, &status, WNOHANG)) > 0)
	;

    exit(0);
}