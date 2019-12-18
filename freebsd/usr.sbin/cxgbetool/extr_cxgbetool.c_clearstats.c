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
typedef  long uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_T4_CLEAR_STATS ; 
 int EINVAL ; 
 int doit (int /*<<< orphan*/ ,long*) ; 
 char* str_to_number (char const*,long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
clearstats(int argc, const char *argv[])
{
	char *p;
	long l;
	uint32_t port;

	if (argc != 1) {
		warnx("incorrect number of arguments.");
		return (EINVAL);
	}

	p = str_to_number(argv[0], &l, NULL);
	if (*p) {
		warnx("invalid port id \"%s\"", argv[0]);
		return (EINVAL);
	}
	port = l;

	return doit(CHELSIO_T4_CLEAR_STATS, &port);
}