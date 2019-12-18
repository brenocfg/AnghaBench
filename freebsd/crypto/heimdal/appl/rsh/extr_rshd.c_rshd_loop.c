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
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ AUTH_KRB5 ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FD_CLR (int,int /*<<< orphan*/ *) ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int FD_SETSIZE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int RSHD_BUFSIZ ; 
 int RSH_BUFSIZ ; 
 scalar_t__ auth_method ; 
 int /*<<< orphan*/  close (int) ; 
 int do_read (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_write (int,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_ivecs (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ivec_in ; 
 int /*<<< orphan*/ * ivec_out ; 
 char* malloc (int) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  net_write (int,char*,int) ; 
 int protocol_version ; 
 int read (int,char*,int) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  syslog_and_die (char*,...) ; 

__attribute__((used)) static void
rshd_loop (int from0, int to0,
	   int to1,   int from1,
	   int to2,   int from2,
	   int have_errsock)
{
    fd_set real_readset;
    int max_fd;
    int count = 2;
    char *buf;

    if(from0 >= FD_SETSIZE || from1 >= FD_SETSIZE || from2 >= FD_SETSIZE)
	errx (1, "fd too large");

#ifdef KRB5
    if(auth_method == AUTH_KRB5 && protocol_version == 2)
	init_ivecs(0, have_errsock);
#endif

    FD_ZERO(&real_readset);
    FD_SET(from0, &real_readset);
    FD_SET(from1, &real_readset);
    FD_SET(from2, &real_readset);
    max_fd = max(from0, max(from1, from2)) + 1;

    buf = malloc(max(RSHD_BUFSIZ, RSH_BUFSIZ));
    if (buf == NULL)
	syslog_and_die("out of memory");

    for (;;) {
	int ret;
	fd_set readset = real_readset;

	ret = select (max_fd, &readset, NULL, NULL, NULL);
	if (ret < 0) {
	    if (errno == EINTR)
		continue;
	    else
		syslog_and_die ("select: %s", strerror(errno));
	}
	if (FD_ISSET(from0, &readset)) {
	    ret = do_read (from0, buf, RSHD_BUFSIZ, ivec_in[0]);
	    if (ret < 0)
		syslog_and_die ("read: %s", strerror(errno));
	    else if (ret == 0) {
		close (from0);
		close (to0);
		FD_CLR(from0, &real_readset);
	    } else
		net_write (to0, buf, ret);
	}
	if (FD_ISSET(from1, &readset)) {
	    ret = read (from1, buf, RSH_BUFSIZ);
	    if (ret < 0)
		syslog_and_die ("read: %s", strerror(errno));
	    else if (ret == 0) {
		close (from1);
		close (to1);
		FD_CLR(from1, &real_readset);
		if (--count == 0)
		    exit (0);
	    } else
		do_write (to1, buf, ret, ivec_out[0]);
	}
	if (FD_ISSET(from2, &readset)) {
	    ret = read (from2, buf, RSH_BUFSIZ);
	    if (ret < 0)
		syslog_and_die ("read: %s", strerror(errno));
	    else if (ret == 0) {
		close (from2);
		close (to2);
		FD_CLR(from2, &real_readset);
		if (--count == 0)
		    exit (0);
	    } else
		do_write (to2, buf, ret, ivec_out[1]);
	}
   }
}