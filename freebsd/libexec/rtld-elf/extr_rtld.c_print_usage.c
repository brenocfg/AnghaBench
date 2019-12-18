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

/* Variables and functions */
 int /*<<< orphan*/  rtld_printf (char*,char const*) ; 

__attribute__((used)) static void
print_usage(const char *argv0)
{

	rtld_printf("Usage: %s [-h] [-f <FD>] [--] <binary> [<args>]\n"
		"\n"
		"Options:\n"
		"  -h        Display this help message\n"
		"  -p        Search in PATH for named binary\n"
		"  -f <FD>   Execute <FD> instead of searching for <binary>\n"
		"  --        End of RTLD options\n"
		"  <binary>  Name of process to execute\n"
		"  <args>    Arguments to the executed process\n", argv0);
}