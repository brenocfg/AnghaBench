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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ AUTH_KRB5 ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FD_CLR (int,int /*<<< orphan*/ *) ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int FD_SETSIZE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int RSH_BUFSIZ ; 
 int /*<<< orphan*/  SHUT_WR ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 scalar_t__ auth_method ; 
 int /*<<< orphan*/  close (int) ; 
 int do_read (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_write (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  init_ivecs (int,int) ; 
 scalar_t__ input ; 
 int /*<<< orphan*/ * ivec_in ; 
 int /*<<< orphan*/ * ivec_out ; 
 scalar_t__ max (int,int) ; 
 int /*<<< orphan*/  net_write (int /*<<< orphan*/ ,char*,int) ; 
 int protocol_version ; 
 int read (int,char*,int) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shutdown (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rsh_loop (int s, int errsock)
{
    fd_set real_readset;
    int count = 1;

#ifdef KRB5
    if(auth_method == AUTH_KRB5 && protocol_version == 2)
	init_ivecs(1, errsock != -1);
#endif

    if (s >= FD_SETSIZE || (errsock != -1 && errsock >= FD_SETSIZE))
	errx (1, "fd too large");

    FD_ZERO(&real_readset);
    FD_SET(s, &real_readset);
    if (errsock != -1) {
	FD_SET(errsock, &real_readset);
	++count;
    }
    if(input)
	FD_SET(STDIN_FILENO, &real_readset);

    for (;;) {
	int ret;
	fd_set readset;
	char buf[RSH_BUFSIZ];

	readset = real_readset;
	ret = select (max(s, errsock) + 1, &readset, NULL, NULL, NULL);
	if (ret < 0) {
	    if (errno == EINTR)
		continue;
	    else
		err (1, "select");
	}
	if (FD_ISSET(s, &readset)) {
	    ret = do_read (s, buf, sizeof(buf), ivec_in[0]);
	    if (ret < 0)
		err (1, "read");
	    else if (ret == 0) {
		close (s);
		FD_CLR(s, &real_readset);
		if (--count == 0)
		    return 0;
	    } else
		net_write (STDOUT_FILENO, buf, ret);
	}
	if (errsock != -1 && FD_ISSET(errsock, &readset)) {
	    ret = do_read (errsock, buf, sizeof(buf), ivec_in[1]);
	    if (ret < 0)
		err (1, "read");
	    else if (ret == 0) {
		close (errsock);
		FD_CLR(errsock, &real_readset);
		if (--count == 0)
		    return 0;
	    } else
		net_write (STDERR_FILENO, buf, ret);
	}
	if (FD_ISSET(STDIN_FILENO, &readset)) {
	    ret = read (STDIN_FILENO, buf, sizeof(buf));
	    if (ret < 0)
		err (1, "read");
	    else if (ret == 0) {
		close (STDIN_FILENO);
		FD_CLR(STDIN_FILENO, &real_readset);
		shutdown (s, SHUT_WR);
	    } else
		do_write (s, buf, ret, ivec_out[0]);
	}
    }
}