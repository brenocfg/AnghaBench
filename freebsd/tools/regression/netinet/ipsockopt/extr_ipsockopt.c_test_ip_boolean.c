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
typedef  int /*<<< orphan*/  newvalue ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,char const*,char*,...) ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int,int*,int*) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int,int*,int) ; 

__attribute__((used)) static void
test_ip_boolean(int sock, const char *socktypename, int option,
    char *optionname, int initial, int rootonly)
{
	int newvalue, val[2];
	socklen_t len;

	/*
	 * The default for a boolean might be true or false.  If it's false,
	 * we will try setting it to true (but using a non-1 value of true).
	 * If it's true, we'll set it to false.
	 */
	if (initial == 0)
		newvalue = 0xff;
	else
		newvalue = 0;

	val[0] = -1;
	val[1] = -1;
	len = sizeof(val);
	if (getsockopt(sock, IPPROTO_IP, option, val, &len) < 0)
		err(-1, "test_ip_boolean: initial getsockopt()");

	if (len != sizeof(val[0]))
		errx(-1, "test_ip_boolean(%s, %s): initial getsockopt() "
		    "returned %d bytes", socktypename, optionname, len);

	if (val[0] == -1)
		errx(-1, "test_ip_boolean(%s, %s): initial getsockopt() "
		    "didn't return data", socktypename, optionname);

	if (val[0] != initial)
		errx(-1, "test_ip_boolean(%s, %s): initial getsockopt() "
		    "returned %d (expected %d)", socktypename, optionname,
		    val[0], initial);

	/*
	 * Set the socket option to a new non-default value.
	 */
	if (setsockopt(sock, IPPROTO_IP, option, &newvalue, sizeof(newvalue))
	    < 0)
		err(-1, "test_ip_boolean(%s, %s): setsockopt() to %d",
		    socktypename, optionname, newvalue);

	/*
	 * Read the value back and see if it is not the default (note: will
	 * not be what we set it to, as we set it to 0xff above).
	 */
	val[0] = -1;
	val[1] = -1;
	len = sizeof(val);
	if (getsockopt(sock, IPPROTO_IP, option, val, &len) < 0)
		err(-1, "test_ip_boolean(%s, %s): getsockopt() after set to "
		    "%d", socktypename, optionname, newvalue);

	if (len != sizeof(val[0]))
		errx(-1, "test_ip_boolean(%s, %s): getsockopt() after set "
		    "to %d returned %d bytes", socktypename, optionname,
		    newvalue, len);

	if (val[0] == -1)
		errx(-1, "test_ip_boolean(%s, %s): getsockopt() after set "
		    "to %d didn't return data", socktypename, optionname,
		    newvalue);

	/*
	 * If we set it to true, check for '1', otherwise '0.
	 */
	if (val[0] != (newvalue ? 1 : 0))
		errx(-1, "test_ip_boolean(%s, %s): getsockopt() after set "
		    "to %d returned %d", socktypename, optionname, newvalue,
		    val[0]);

	/*
	 * Reset to initial value.
	 */
	newvalue = initial;
	if (setsockopt(sock, IPPROTO_IP, option, &newvalue, sizeof(newvalue))
	    < 0)
		err(-1, "test_ip_boolean(%s, %s): setsockopt() to reset",
		    socktypename, optionname);

	/*
	 * Check reset version.
	 */
	val[0] = -1;
	val[1] = -1;
	len = sizeof(val);
	if (getsockopt(sock, IPPROTO_IP, option, val, &len) < 0)
		err(-1, "test_ip_boolean(%s, %s): getsockopt() after reset",
		    socktypename, optionname);

	if (len != sizeof(val[0]))
		errx(-1, "test_ip_boolean(%s, %s): getsockopt() after reset "
		    "returned %d bytes", socktypename, optionname, len);

	if (val[0] == -1)
		errx(-1, "test_ip_boolean(%s, %s): getsockopt() after reset "
		    "didn't return data", socktypename, optionname);

	if (val[0] != newvalue)
		errx(-1, "test_ip_boolean(%s, %s): getsockopt() after reset "
		    "returned %d", socktypename, optionname, newvalue);
}