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
typedef  int /*<<< orphan*/  uc ;
typedef  scalar_t__ u_char ;
typedef  int socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_IP ; 
 int WARN_SUCCESS ; 
 int /*<<< orphan*/  err (int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*,char const*,scalar_t__,scalar_t__) ; 
 int getsockopt (int,int /*<<< orphan*/ ,int,scalar_t__*,int*) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  warnx (char*,char const*,char const*) ; 

__attribute__((used)) static void
test_u_char(int optname, const char *optstring, u_char defaultv,
    u_char modifiedv, u_char fakev, const char *socktype, int sock,
    int flags)
{
	socklen_t socklen;
	u_char uc;
	int ret;

	/*
	 * Check that we read back the expected default.
	 */
	uc = fakev;
	socklen = sizeof(uc);

	ret = getsockopt(sock, IPPROTO_IP, optname, &uc, &socklen);
	if (ret < 0)
		err(-1, "FAIL: getsockopt(%s, IPPROTO_IP, %s)",
		    socktype, optstring);
	if (ret == 0 && (flags & WARN_SUCCESS))
		warnx("WARN: getsockopt(%s, IPPROTO_IP, %s) returned 0",
		    socktype, optstring);
	if (uc != defaultv)
		errx(-1, "FAIL: getsockopt(%s, IPPROTO_IP, %s) default is "
		    "%d not %d", socktype, optstring, uc, defaultv);

	/*
	 * Set to a modifiedv value, read it back and make sure it got there.
	 */
	uc = modifiedv;
	ret = setsockopt(sock, IPPROTO_IP, optname, &uc, sizeof(uc));
	if (ret == -1)
		err(-1, "FAIL: setsockopt(%s, IPPROTO_IP, %s)",
		    socktype, optstring);
	if (ret == 0 && (flags & WARN_SUCCESS))
		warnx("WARN: setsockopt(%s, IPPROTO_IP, %s) returned 0",
		    socktype, optstring);

	uc = fakev;
	socklen = sizeof(uc);
	ret = getsockopt(sock, IPPROTO_IP, optname, &uc, &socklen);
	if (ret < 0)
		err(-1, "FAIL: getsockopt(%s, IPPROTO_IP, %s)",
		    socktype, optstring);
	if (ret == 0 && (flags & WARN_SUCCESS))
		warnx("WARN: getsockopt(%s, IPPROTO_IP, %s) returned 0",
		    socktype, optstring);
	if (uc != modifiedv)
		errx(-1, "FAIL: getsockopt(%s, IPPROTO_IP, %s) set value is "
		    "%d not %d", socktype, optstring, uc, modifiedv);
}