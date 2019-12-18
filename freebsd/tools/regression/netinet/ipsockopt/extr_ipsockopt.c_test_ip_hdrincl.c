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
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  flag ;

/* Variables and functions */
 scalar_t__ ENOPROTOOPT ; 
 int HISTORICAL_INP_HDRINCL ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IP_HDRINCL ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,int,...) ; 
 int geteuid () ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  warnx (char*,int) ; 

__attribute__((used)) static void
test_ip_hdrincl(void)
{
	int flag[2], sock;
	socklen_t len;

	/*
	 * Try to receive or set the IP_HDRINCL flag on a TCP socket.
	 */
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		err(-1, "test_ip_hdrincl(): socket(SOCK_STREAM)");

	flag[0] = -1;
	len = sizeof(flag[0]);
	if (getsockopt(sock, IPPROTO_IP, IP_HDRINCL, flag, &len) == 0)
		err(-1, "test_ip_hdrincl(): initial getsockopt(IP_HDRINCL)");

	if (errno != ENOPROTOOPT)
		errx(-1, "test_ip_hdrincl(): initial getsockopt(IP_HDRINC) "
		    "returned %d (%s) not ENOPROTOOPT", errno,
		    strerror(errno));

	flag[0] = 1;
	if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, flag, sizeof(flag[0]))
	    == 0)
		err(-1,"test_ip_hdrincl(): setsockopt(IP_HDRINCL) on TCP "
		    "succeeded\n");

	if (errno != ENOPROTOOPT)
		errx(-1, "test_ip_hdrincl(): setsockopt(IP_HDRINCL) on TCP "
		    "returned %d (%s) not ENOPROTOOPT\n", errno,
		    strerror(errno));

	close(sock);

	/*
	 * Try to receive or set the IP_HDRINCL flag on a UDP socket.
	 */
	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock == -1)
		err(-1, "test_ip_hdrincl(): socket(SOCK_DGRAM");

	flag[0] = -1;
	len = sizeof(flag[0]);
	if (getsockopt(sock, IPPROTO_IP, IP_HDRINCL, flag, &len) == 0)
		err(-1, "test_ip_hdrincl(): getsockopt(IP_HDRINCL) on UDP "
		    "succeeded\n");

	if (errno != ENOPROTOOPT)
		errx(-1, "test_ip_hdrincl(): getsockopt(IP_HDRINCL) on UDP "
		    "returned %d (%s) not ENOPROTOOPT\n", errno,
		    strerror(errno));

	if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, flag, sizeof(flag[0]))
	    == 0)
		err(-1, "test_ip_hdrincl(): setsockopt(IP_HDRINCL) on UDP "
		    "succeeded\n");

	if (errno != ENOPROTOOPT)
		errx(-1, "test_ip_hdrincl(): setsockopt(IP_HDRINCL) on UDP "
		    "returned %d (%s) not ENOPROTOOPT\n", errno,
		    strerror(errno));

	close(sock);

	/*
	 * Now try on a raw socket.  Access ontrol should prevent non-root
	 * users from creating the raw socket, so check that here based on
	 * geteuid().  If we're non-root, we just return assuming the socket
	 * create fails since the remainder of the tests apply only on a raw
	 * socket.
	 */
	sock = socket(PF_INET, SOCK_RAW, 0);
	if (geteuid() != 0) {
		if (sock != -1)
			errx(-1, "test_ip_hdrincl: created raw socket as "
			    "uid %d", geteuid());
		return;
	}
	if (sock == -1)
		err(-1, "test_ip_hdrincl(): socket(PF_INET, SOCK_RAW)");

	/*
	 * Make sure the initial value of the flag is 0 (disabled).
	 */
	flag[0] = -1;
	flag[1] = -1;
	len = sizeof(flag);
	if (getsockopt(sock, IPPROTO_IP, IP_HDRINCL, flag, &len) < 0)
		err(-1, "test_ip_hdrincl(): getsockopt(IP_HDRINCL) on raw "
		    "socket");

	if (len != sizeof(flag[0]))
		errx(-1, "test_ip_hdrincl(): %d bytes returned on "
		    "initial get\n", len);

	if (flag[0] != 0)
		errx(-1, "test_ip_hdrincl(): initial flag value of %d\n",
		    flag[0]);

	/*
	 * Enable the IP_HDRINCL flag.
	 */
	flag[0] = 1;
	if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, flag, sizeof(flag[0]))
	    < 0)
		err(-1, "test_ip_hdrincl(): setsockopt(IP_HDRINCL, 1)");

	/*
	 * Check that the IP_HDRINCL flag was set.
	 */
	flag[0] = -1;
	flag[1] = -1;
	len = sizeof(flag);
	if (getsockopt(sock, IPPROTO_IP, IP_HDRINCL, flag, &len) < 0)
		err(-1, "test_ip_hdrincl(): getsockopt(IP_HDRINCL) after "
		    "set");

	if (flag[0] == 0)
		errx(-1, "test_ip_hdrincl(): getsockopt(IP_HDRINCL) "
		    "after set had flag of %d\n", flag[0]);

#define	HISTORICAL_INP_HDRINCL	8
	if (flag[0] != HISTORICAL_INP_HDRINCL)
		warnx("test_ip_hdrincl(): WARNING: getsockopt(IP_H"
		    "DRINCL) after set had non-historical value of %d\n",
		    flag[0]);

	/*
	 * Reset the IP_HDRINCL flag to 0.
	 */
	flag[0] = 0;
	if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, flag, sizeof(flag[0]))
	    < 0)
		err(-1, "test_ip_hdrincl(): setsockopt(IP_HDRINCL, 0)");

	/*
	 * Check that the IP_HDRINCL flag was reset to 0.
	 */
	flag[0] = -1;
	flag[1] = -1;
	len = sizeof(flag);
	if (getsockopt(sock, IPPROTO_IP, IP_HDRINCL, flag, &len) < 0)
		err(-1, "test_ip_hdrincl(): getsockopt(IP_HDRINCL) after "
		    "reset");

	if (flag[0] != 0)
		errx(-1, "test_ip_hdrincl(): getsockopt(IP_HDRINCL) "
		    "after set had flag of %d\n", flag[0]);

	close(sock);
}