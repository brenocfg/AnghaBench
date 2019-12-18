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
struct ip_mreq {int /*<<< orphan*/  imr_interface; int /*<<< orphan*/  imr_multiaddr; } ;
typedef  int /*<<< orphan*/  imr ;

/* Variables and functions */
 scalar_t__ EADDRINUSE ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IP_ADD_MEMBERSHIP ; 
 int WARN_SUCCESS ; 
 int /*<<< orphan*/  err (int,char*,char const*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ip_mreq*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  warnx (char*,char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_add_multi(int sock, const char *socktype, struct ip_mreq imr,
    int flags)
{
	char buf[128];
	int ret;

	ret = setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &imr,
	    sizeof(imr));
	if (ret < 0) {
		strlcpy(buf, inet_ntoa(imr.imr_multiaddr), 128);
		err(-1, "FAIL: setsockopt(%s, IPPROTO_IP, IP_ADD_MEMBERSHIP "
		    "%s, %s)", socktype, buf, inet_ntoa(imr.imr_interface));
	}
	if (ret == 0 && (flags & WARN_SUCCESS)) {
		strlcpy(buf, inet_ntoa(imr.imr_multiaddr), 128);
		warnx("WARN: setsockopt(%s, IPPROTO_IP, IP_ADD_MEMBERSHIP "
		    "%s, %s) returned 0", socktype, buf,
		    inet_ntoa(imr.imr_interface));
	}

	/* Try to add a second time to make sure it got there. */
	ret = setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &imr,
	    sizeof(imr));
	if (ret == 0) {
		strlcpy(buf, inet_ntoa(imr.imr_multiaddr), 128);
		err(-1, "FAIL: setsockopt(%s, IPPROTO_IP, IP_ADD_MEMBERSHIP "
		    "%s, %s) dup returned 0", socktype, buf,
		    inet_ntoa(imr.imr_interface));
	}
	if (ret < 0 && errno != EADDRINUSE) {
		strlcpy(buf, inet_ntoa(imr.imr_multiaddr), 128);
		err(-1, "FAIL: setsockopt(%s, IPPROTO_IP, IP_ADD_MEMBERSHIP "
		    "%s, %s)", socktype, buf, inet_ntoa(imr.imr_interface));
	}
}