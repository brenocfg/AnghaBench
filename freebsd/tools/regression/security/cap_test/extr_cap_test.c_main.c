#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  t_name; } ;

/* Variables and functions */
 TYPE_1__* all_tests ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  execute (int,TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int test_count ; 

int
main(int argc, char *argv[])
{

	/*
	 * If no tests have been specified at the command line, run them all.
	 */
	if (argc == 1) {
		printf("1..%d\n", test_count);

		for (int i = 0; i < test_count; i++)
			execute(i + 1, all_tests + i);
		return (0);
	}

	/*
	 * Otherwise, run only the specified tests.
	 */
	printf("1..%d\n", argc - 1);
	for (int i = 1; i < argc; i++)
	{
		int found = 0;
		for (int j = 0; j < test_count; j++) {
			if (strncmp(argv[i], all_tests[j].t_name,
			    strlen(argv[i])) == 0) {
				found = 1;
				execute(i, all_tests + j);
				break;
			}
		}

		if (found == 0)
			errx(-1, "No such test '%s'", argv[i]);
	}

	return (0);
}