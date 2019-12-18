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
typedef  int /*<<< orphan*/  socktypeset ;

/* Variables and functions */
 int /*<<< orphan*/  BOOLEAN_ANYONE ; 
 int /*<<< orphan*/  IP_FAITH ; 
 int /*<<< orphan*/  IP_MULTICAST_LOOP ; 
 int /*<<< orphan*/  IP_MULTICAST_TTL ; 
 int /*<<< orphan*/  IP_ONESBCAST ; 
 int /*<<< orphan*/  IP_RECVDSTADDR ; 
 int /*<<< orphan*/  IP_RECVIF ; 
 int /*<<< orphan*/  IP_RECVOPTS ; 
 int /*<<< orphan*/  IP_RECVRETOPTS ; 
 int /*<<< orphan*/  IP_RECVTTL ; 
 int /*<<< orphan*/  IP_TOS ; 
 int /*<<< orphan*/  IP_TTL ; 
 int SOCK_DGRAM ; 
 int SOCK_RAW ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,char const*,int) ; 
 int get_socket (int,int) ; 
 scalar_t__ geteuid () ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  test_ip_boolean (int,char const*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_ip_hdrincl () ; 
 int /*<<< orphan*/  test_ip_multicast_if (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_ip_multicast_membership (int,char const*) ; 
 int /*<<< orphan*/  test_ip_multicast_vif (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_ip_uchar (int,char const*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
testsuite(int priv)
{
	const char *socktypenameset[] = {"SOCK_DGRAM", "SOCK_STREAM",
	    "SOCK_RAW"};
	int socktypeset[] = {SOCK_DGRAM, SOCK_STREAM, SOCK_RAW};
	const char *socktypename;
	int i, sock, socktype;

	test_ip_hdrincl();

	for (i = 0; i < sizeof(socktypeset)/sizeof(int); i++) {
		socktype = socktypeset[i];
		socktypename = socktypenameset[i];

		/*
		 * If we can't acquire root privilege, we can't open raw
		 * sockets, so don't actually try.
		 */
		if (getuid() != 0 && socktype == SOCK_RAW)
			continue;
		if (geteuid() != 0 && !priv && socktype == SOCK_RAW)
			continue;

		/*
		 * XXXRW: On 5.3, this seems not to work for SOCK_RAW.
		 */
		sock = get_socket(socktype, priv);
		if (sock == -1)
			err(-1, "get_socket(%s, %d) for test_ip_uchar(IP_TOS)",
			    socktypename, priv);
		test_ip_uchar(sock, socktypename, IP_TOS, "IP_TOS", 0);
		close(sock);

		sock = get_socket(socktype, priv);
		if (sock == -1)
			err(-1, "get_socket(%s %d) for test_ip_uchar(IP_TTL)",
			    socktypename, priv);
		test_ip_uchar(sock, socktypename, IP_TTL, "IP_TTL", 64);
		close(sock);

		sock = get_socket(socktype, priv);
		if (sock == -1)
			err(-1, "get_socket(%s, %d) for test_ip_boolean"
			    "(IP_RECVOPTS)", socktypename, priv);
		test_ip_boolean(sock, socktypename, IP_RECVOPTS,
		    "IP_RECVOPTS", 0, BOOLEAN_ANYONE);
		close(sock);

		sock = get_socket(socktype, priv);
		if (sock == -1)
			err(-1, "get_socket(%s, %d) for test_ip_boolean"
			     "(IP_RECVRETOPTS)", socktypename, priv);
		test_ip_boolean(sock, socktypename, IP_RECVRETOPTS,
		    "IP_RECVRETOPTS", 0, BOOLEAN_ANYONE);
		close(sock);

		sock = get_socket(socktype, priv);
		if (sock == -1)
			err(-1, "get_socket(%s, %d) for test_ip_boolean"
			    "(IP_RECVDSTADDR)", socktypename, priv);
		test_ip_boolean(sock, socktypename, IP_RECVDSTADDR,
		    "IP_RECVDSTADDR", 0, BOOLEAN_ANYONE);
		close(sock);

		sock = get_socket(socktype, priv);
		if (sock == -1)
			err(-1, "get_socket(%s, %d) for test_ip_boolean"
			    "(IP_RECVTTL)", socktypename, priv);
		test_ip_boolean(sock, socktypename, IP_RECVTTL, "IP_RECVTTL",
		    0, BOOLEAN_ANYONE);
		close(sock);

		sock = get_socket(socktype, priv);
		if (sock == -1)
			err(-1, "get_socket(%s, %d) for test_ip_boolean"
			    "(IP_RECVIF)", socktypename, priv);
		test_ip_boolean(sock, socktypename, IP_RECVIF, "IP_RECVIF",
		    0, BOOLEAN_ANYONE);
		close(sock);

		sock = get_socket(socktype, priv);
		if (sock == -1)
			err(-1, "get_socket(%s, %d) for test_ip_boolean"
			    "(IP_FAITH)", socktypename, priv);
		test_ip_boolean(sock, socktypename, IP_FAITH, "IP_FAITH", 0,
		    BOOLEAN_ANYONE);
		close(sock);

		sock = get_socket(socktype, priv);
		if (sock == -1)
			err(-1, "get_socket(%s, %d) for test_ip_boolean"
			    "(IP_ONESBCAST)", socktypename, priv);
		test_ip_boolean(sock, socktypename, IP_ONESBCAST,
		    "IP_ONESBCAST", 0, BOOLEAN_ANYONE);
		close(sock);

		/*
		 * Test the multicast TTL exactly as we would the regular
		 * TTL, only expect a different default.
		 */
		sock = get_socket(socktype, priv);
		if (sock == -1)
			err(-1, "get_socket(%s, %d) for IP_MULTICAST_TTL",
			    socktypename, priv);
		test_ip_uchar(sock, socktypename, IP_MULTICAST_TTL,
		    "IP_MULTICAST_TTL", 1);
		close(sock);

		/*
		 * The multicast loopback flag can be tested using our
		 * boolean tester, but only because the FreeBSD API is a bit
		 * more flexible than earlir APIs and will accept an int as
		 * well as a u_char.  Loopback is enabled by default.
		 */
		sock = get_socket(socktype, priv);
		if (sock == -1)
			err(-1, "get_socket(%s, %d) for IP_MULTICAST_LOOP",
			    socktypename, priv);
		test_ip_boolean(sock, socktypename, IP_MULTICAST_LOOP,
		    "IP_MULTICAST_LOOP", 1, BOOLEAN_ANYONE);
		close(sock);

		sock = get_socket(socktype, priv);
		if (sock == -1)
			err(-1, "get_socket(%s, %d) for test_ip_options",
			    socktypename, priv);
		//test_ip_options(sock, socktypename);
		close(sock);

		sock = get_socket(socktype, priv);
		if (sock == -1)
			err(-1, "get_socket(%s, %d) for test_ip_options",
			    socktypename, priv);
		test_ip_multicast_membership(sock, socktypename);
		close(sock);

		test_ip_multicast_if(0, NULL);
		test_ip_multicast_vif(0, NULL);
		/*
		 * XXX: Still need to test:
		 * IP_PORTRANGE
		 * IP_IPSEC_POLICY?
		 */
	}
}