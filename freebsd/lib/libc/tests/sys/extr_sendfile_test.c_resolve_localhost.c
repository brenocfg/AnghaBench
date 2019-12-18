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
struct addrinfo {int ai_family; int ai_flags; int ai_socktype; } ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int AI_ADDRCONFIG ; 
 int AI_NUMERICHOST ; 
 int AI_NUMERICSERV ; 
 int /*<<< orphan*/  ATF_REQUIRE_EQ_MSG (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ asprintf (char**,char*,int) ; 
 int /*<<< orphan*/  atf_tc_fail (char*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char const*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
resolve_localhost(struct addrinfo **res, int domain, int type, int port)
{
	const char *host;
	char *serv;
	struct addrinfo hints;
	int error;

	switch (domain) {
	case AF_INET:
		host = "127.0.0.1";
		break;
	case AF_INET6:
		host = "::1";
		break;
	default:
		atf_tc_fail("unhandled domain: %d", domain);
	}

	ATF_REQUIRE_MSG(asprintf(&serv, "%d", port) >= 0,
	    "asprintf failed: %s", strerror(errno));

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = domain;
	hints.ai_flags = AI_ADDRCONFIG|AI_NUMERICSERV|AI_NUMERICHOST;
	hints.ai_socktype = type;

	error = getaddrinfo(host, serv, &hints, res);
	ATF_REQUIRE_EQ_MSG(error, 0,
	    "getaddrinfo failed: %s", gai_strerror(error));
	free(serv);
}