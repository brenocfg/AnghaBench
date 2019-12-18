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
struct in_addr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  ia ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_IP ; 
 int WARN_SUCCESS ; 
 int /*<<< orphan*/  err (int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int getsockopt (int,int /*<<< orphan*/ ,int,struct in_addr*,int*) ; 
 int /*<<< orphan*/  inet_ntoa (struct in_addr) ; 
 scalar_t__ memcmp (struct in_addr*,struct in_addr*,int) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int,struct in_addr*,int) ; 
 int /*<<< orphan*/  warnx (char*,char const*,char const*) ; 

__attribute__((used)) static void
test_in_addr(int optname, const char *optstring, struct in_addr defaultv,
    struct in_addr modifiedv, struct in_addr fakev, const char *socktype,
    int sock, int flags)
{
	socklen_t socklen;
	struct in_addr ia;
	int ret;

	/*
	 * Check that we read back the expected default.
	 */
	ia = fakev;
	socklen = sizeof(ia);

	ret = getsockopt(sock, IPPROTO_IP, optname, &ia, &socklen);
	if (ret < 0)
		err(-1, "FAIL: getsockopt(%s, IPPROTO_IP, %s)",
		    socktype, optstring);
	if (ret == 0 && (flags & WARN_SUCCESS))
		warnx("WARN: getsockopt(%s, IPPROTO_IP, %s) returned 0",
		    socktype, optstring);
	if (memcmp(&ia, &defaultv, sizeof(struct in_addr)))
		errx(-1, "FAIL: getsockopt(%s, IPPROTO_IP, %s) default is "
		    "%s not %s", socktype, optstring, inet_ntoa(ia),
		    inet_ntoa(defaultv));

	/*
	 * Set to a modifiedv value, read it back and make sure it got there.
	 */
	ia = modifiedv;
	ret = setsockopt(sock, IPPROTO_IP, optname, &ia, sizeof(ia));
	if (ret == -1)
		err(-1, "FAIL: setsockopt(%s, IPPROTO_IP, %s)",
		    socktype, optstring);
	if (ret == 0 && (flags & WARN_SUCCESS))
		warnx("WARN: setsockopt(%s, IPPROTO_IP, %s) returned 0",
		    socktype, optstring);

	ia = fakev;
	socklen = sizeof(ia);
	ret = getsockopt(sock, IPPROTO_IP, optname, &ia, &socklen);
	if (ret < 0)
		err(-1, "FAIL: getsockopt(%s, IPPROTO_IP, %s)",
		    socktype, optstring);
	if (ret == 0 && (flags & WARN_SUCCESS))
		warnx("WARN: getsockopt(%s, IPPROTO_IP, %s) returned 0",
		    socktype, optstring);
	if (memcmp(&ia, &modifiedv, sizeof(struct in_addr)))
		errx(-1, "FAIL: getsockopt(%s, IPPROTO_IP, %s) set value is "
		    "%s not %s", socktype, optstring, inet_ntoa(ia),
		    inet_ntoa(modifiedv));
}