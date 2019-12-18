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
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  usage (char*) ; 
 int write_sh_tests (char*,int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	int opt;

	while ((opt = getopt(argc, argv, "s:")) != -1) {
		switch (opt) {
		case 's':
			return (write_sh_tests(argv[0], atoi(optarg)));
		default:
			usage(argv[0]);
			exit(1);
		}
	}
	usage(argv[0]);
	exit(1);
}