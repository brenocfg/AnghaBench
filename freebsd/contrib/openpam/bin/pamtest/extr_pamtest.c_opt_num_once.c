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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 char* optarg ; 
 int /*<<< orphan*/  stderr ; 
 long strtol (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static void
opt_num_once(int opt, long *num, const char *arg)
{
	char *end;
	long l;

	l = strtol(arg, &end, 0);
	if (end == optarg || *end != '\0') {
		fprintf(stderr,
		    "The -%c option expects a numeric argument\n", opt);
		usage();
	}
	*num = l;
}