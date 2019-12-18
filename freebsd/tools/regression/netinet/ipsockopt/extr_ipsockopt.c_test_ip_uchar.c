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
typedef  int /*<<< orphan*/  val ;
typedef  int socklen_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  err (int,char*,char const*,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,char const*,char const*,...) ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int,int*,int*) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int,int*,int) ; 

__attribute__((used)) static void
test_ip_uchar(int sock, const char *socktypename, int option,
    const char *optionname, int initial)
{
	int val[2];
	socklen_t len;

	/*
	 * Check that the initial value is 0, and that the size is one
	 * u_char;
	 */
	val[0] = -1;
	val[1] = -1;
	len = sizeof(val);
	if (getsockopt(sock, IPPROTO_IP, option, val, &len) < 0)
		err(-1, "test_ip_uchar(%s, %s): initial getsockopt()",
		    socktypename, optionname);

	if (len != sizeof(val[0]))
		errx(-1, "test_ip_uchar(%s, %s): initial getsockopt() "
		    "returned %d bytes", socktypename, optionname, len);

	if (val[0] == -1)
		errx(-1, "test_ip_uchar(%s, %s): initial getsockopt() didn't "
		    "return data", socktypename, optionname);

	if (val[0] != initial)
		errx(-1, "test_ip_uchar(%s, %s): initial getsockopt() "
		    "returned value of %d, not %d", socktypename, optionname,
		    val[0], initial);

	/*
	 * Set the field to a valid value.
	 */
	val[0] = 128;
	val[1] = -1;
	if (setsockopt(sock, IPPROTO_IP, option, val, sizeof(val[0])) < 0)
		err(-1, "test_ip_uchar(%s, %s): setsockopt(128)",
		    socktypename, optionname);

	/*
	 * Check that when we read back the field, we get the same value.
	 */
	val[0] = -1;
	val[1] = -1;
	len = sizeof(val);
	if (getsockopt(sock, IPPROTO_IP, option, val, &len) < 0)
		err(-1, "test_ip_uchar(%s, %s): getsockopt() after set to "
		    "128", socktypename, optionname);

	if (len != sizeof(val[0]))
		errx(-1, "test_ip_uchar(%s, %s): getsockopt() after set to "
		    "128 returned %d bytes", socktypename, optionname, len);

	if (val[0] == -1)
		errx(-1, "test_ip_uchar(%s, %s): getsockopt() after set to "
		    "128 didn't return data", socktypename, optionname);

	if (val[0] != 128)
		errx(-1, "test_ip_uchar(%s, %s): getsockopt() after set to "
		    "128 returned %d", socktypename, optionname, val[0]);

	/*
	 * Reset the value to 0, check that it was reset.
	 */
	val[0] = 0;
	val[1] = 0;
	if (setsockopt(sock, IPPROTO_IP, option, val, sizeof(val[0])) < 0)
		err(-1, "test_ip_uchar(%s, %s): setsockopt() to reset from "
		    "128", socktypename, optionname);

	if (len != sizeof(val[0]))
		errx(-1, "test_ip_uchar(%s, %s): getsockopt() after reset "
		   "from 128 returned %d bytes", socktypename, optionname,
		    len);

	if (val[0] == -1)
		errx(-1, "test_ip_uchar(%s, %s): getsockopt() after reset "
		    "from 128 didn't return data", socktypename, optionname);

	if (val[0] != 0)
		errx(-1, "test_ip_uchar(%s, %s): getsockopt() after reset "
		    "from 128 returned %d", socktypename, optionname,
		    val[0]);

	/*
	 * Set the value to something out of range and check that it comes
	 * back truncated, or that we get EINVAL back.  Traditional u_char
	 * IP socket options truncate, but newer ones (such as multicast
	 * socket options) will return EINVAL.
	 */
	val[0] = 32000;
	val[1] = -1;
	if (setsockopt(sock, IPPROTO_IP, option, val, sizeof(val[0])) < 0) {
		/*
		 * EINVAL is a fine outcome, no need to run the truncation
		 * tests.
		 */
		if (errno == EINVAL)
			return;
		err(-1, "test_ip_uchar(%s, %s): getsockopt(32000)",
		    socktypename, optionname);
	}

	val[0] = -1;
	val[1] = -1;
	len = sizeof(val);
	if (getsockopt(sock, IPPROTO_IP, option, val, &len) < 0)
		err(-1, "test_ip_uchar(%s, %s): getsockopt() after set to "
		    "32000", socktypename, optionname);

	if (len != sizeof(val[0]))
		errx(-1, "test_ip_uchar(%s, %s): getsockopt() after set to "
		    "32000 returned %d bytes", socktypename, optionname,
		    len);

	if (val[0] == -1)
		errx(-1, "test_ip_uchar(%s, %s): getsockopt() after set to "
		    "32000 didn't return data", socktypename, optionname);

	if (val[0] == 32000)
		errx(-1, "test_ip_uchar(%s, %s): getsockopt() after set to "
		    "32000 returned 32000: failed to truncate", socktypename,
		    optionname);
}