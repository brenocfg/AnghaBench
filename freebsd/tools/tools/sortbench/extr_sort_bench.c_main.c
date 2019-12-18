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
typedef  enum test { ____Placeholder_test } test ;
typedef  enum sort { ____Placeholder_sort } sort ;

/* Variables and functions */
 int INVALID_ALG ; 
 int INVALID_TEST ; 
 int NARGS ; 
 int atoi (char*) ; 
 int parse_alg (char*) ; 
 int parse_test (char*) ; 
 int pow (int,int) ; 
 int /*<<< orphan*/  run_bench (int,int,int,int) ; 
 int /*<<< orphan*/  usage (char const*) ; 

int
main(int argc, char *argv[])
{
	const char *progname = argv[0];
	int runs, elts;
	if (argc != NARGS)
		usage(progname);

	enum sort s = parse_alg(argv[1]);
	if (s == INVALID_ALG)
		usage(progname);

	enum test t = parse_test(argv[2]);
	if (t == INVALID_TEST)
		usage(progname);

	runs = atoi(argv[3]);
	elts = pow(2, atoi(argv[4]));

	run_bench(s, t, runs, elts);
}