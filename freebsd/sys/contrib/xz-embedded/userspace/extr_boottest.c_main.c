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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  test_buf_to_buf () ; 
 int /*<<< orphan*/  test_buf_to_cb () ; 
 int /*<<< orphan*/  test_cb_to_buf () ; 
 int /*<<< orphan*/  test_cb_to_cb () ; 

int main(int argc, char **argv)
{
	if (argc != 2)
		fprintf(stderr, "Usage: %s [bb|bc|cc|cb]\n", argv[0]);
	else if (strcmp(argv[1], "bb") == 0)
		test_buf_to_buf();
	else if (strcmp(argv[1], "bc") == 0)
		test_buf_to_cb();
	else if (strcmp(argv[1], "cc") == 0)
		test_cb_to_cb();
	else if (strcmp(argv[1], "cb") == 0)
		test_cb_to_buf();
	else
		fprintf(stderr, "Usage: %s [bb|bc|cc|cb]\n", argv[0]);

	return 0;
}