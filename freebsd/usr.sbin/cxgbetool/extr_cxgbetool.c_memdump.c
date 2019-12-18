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
 int EINVAL ; 
 int read_mem (long,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_mem ; 
 char* str_to_number (char const*,long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
memdump(int argc, const char *argv[])
{
	char *p;
	long l;
	uint32_t addr, len;

	if (argc != 2) {
		warnx("incorrect number of arguments.");
		return (EINVAL);
	}

	p = str_to_number(argv[0], &l, NULL);
	if (*p) {
		warnx("invalid address \"%s\"", argv[0]);
		return (EINVAL);
	}
	addr = l;

	p = str_to_number(argv[1], &l, NULL);
	if (*p) {
		warnx("memdump: invalid length \"%s\"", argv[1]);
		return (EINVAL);
	}
	len = l;

	return (read_mem(addr, len, show_mem));
}