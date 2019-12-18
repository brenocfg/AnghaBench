#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
typedef  int /*<<< orphan*/  str ;
typedef  int socklen_t ;
typedef  scalar_t__ krb5_ssize_t ;
typedef  int krb5_socklen_t ;
typedef  int /*<<< orphan*/  krb5_realm ;
typedef  int /*<<< orphan*/  krb5_keytab ;
typedef  int krb5_error_code ;
struct TYPE_5__ {unsigned int len; int /*<<< orphan*/ * val; } ;
typedef  TYPE_1__ krb5_addresses ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  __ss ;

/* Variables and functions */
 int BUFSIZ ; 
 int EINTR ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int FD_SETSIZE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  context ; 
 int errno ; 
 scalar_t__ exit_flag ; 
 TYPE_1__ explicit_addresses ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  krb5_addr2sockaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sockaddr*,int*,int) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  krb5_free_addresses (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_free_host_realm (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int krb5_get_all_server_addrs (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int krb5_get_default_realms (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int krb5_print_address (int /*<<< orphan*/ *,char*,int,size_t*) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,int,char*,char*) ; 
 int* malloc (unsigned int) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  process (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct sockaddr*,int,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ recvfrom (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 scalar_t__ select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

__attribute__((used)) static int
doit (krb5_keytab keytab, int port)
{
    krb5_error_code ret;
    int *sockets;
    int maxfd;
    krb5_realm *realms;
    krb5_addresses addrs;
    unsigned n, i;
    fd_set real_fdset;
    struct sockaddr_storage __ss;
    struct sockaddr *sa = (struct sockaddr *)&__ss;

    ret = krb5_get_default_realms(context, &realms);
    if (ret)
	krb5_err (context, 1, ret, "krb5_get_default_realms");

    if (explicit_addresses.len) {
	addrs = explicit_addresses;
    } else {
	ret = krb5_get_all_server_addrs (context, &addrs);
	if (ret)
	    krb5_err (context, 1, ret, "krb5_get_all_server_addrs");
    }
    n = addrs.len;

    sockets = malloc (n * sizeof(*sockets));
    if (sockets == NULL)
	krb5_errx (context, 1, "out of memory");
    maxfd = -1;
    FD_ZERO(&real_fdset);
    for (i = 0; i < n; ++i) {
	krb5_socklen_t sa_size = sizeof(__ss);

	krb5_addr2sockaddr (context, &addrs.val[i], sa, &sa_size, port);

	sockets[i] = socket (sa->sa_family, SOCK_DGRAM, 0);
	if (sockets[i] < 0)
	    krb5_err (context, 1, errno, "socket");
	if (bind (sockets[i], sa, sa_size) < 0) {
	    char str[128];
	    size_t len;
	    int save_errno = errno;

	    ret = krb5_print_address (&addrs.val[i], str, sizeof(str), &len);
	    if (ret)
		strlcpy(str, "unknown address", sizeof(str));
	    krb5_warn (context, save_errno, "bind(%s)", str);
	    continue;
	}
	maxfd = max (maxfd, sockets[i]);
	if (maxfd >= FD_SETSIZE)
	    krb5_errx (context, 1, "fd too large");
	FD_SET(sockets[i], &real_fdset);
    }
    if (maxfd == -1)
	krb5_errx (context, 1, "No sockets!");

    while(exit_flag == 0) {
	krb5_ssize_t retx;
	fd_set fdset = real_fdset;

	retx = select (maxfd + 1, &fdset, NULL, NULL, NULL);
	if (retx < 0) {
	    if (errno == EINTR)
		continue;
	    else
		krb5_err (context, 1, errno, "select");
	}
	for (i = 0; i < n; ++i)
	    if (FD_ISSET(sockets[i], &fdset)) {
		u_char buf[BUFSIZ];
		socklen_t addrlen = sizeof(__ss);

		retx = recvfrom(sockets[i], buf, sizeof(buf), 0,
				sa, &addrlen);
		if (retx < 0) {
		    if(errno == EINTR)
			break;
		    else
			krb5_err (context, 1, errno, "recvfrom");
		}

		process (realms, keytab, sockets[i],
			 &addrs.val[i],
			 sa, addrlen,
			 buf, retx);
	    }
    }

    for (i = 0; i < n; ++i)
	close(sockets[i]);
    free(sockets);

    krb5_free_addresses (context, &addrs);
    krb5_free_host_realm (context, realms);
    krb5_free_context (context);
    return 0;
}