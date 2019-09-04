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
struct clar_report {char* suite; char* test; } ;
struct clar_error {char* file; int line_number; char* error_msg; char* description; } ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void clar_print_error(int num, const struct clar_report *report, const struct clar_error *error)
{
	printf("  %d) Failure:\n", num);

	printf("%s::%s [%s:%d]\n",
		report->suite,
		report->test,
		error->file,
		error->line_number);

	printf("  %s\n", error->error_msg);

	if (error->description != NULL)
		printf("  %s\n", error->description);

	printf("\n");
	fflush(stdout);
}