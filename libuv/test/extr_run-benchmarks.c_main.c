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
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int maybe_run_test (int,char**) ; 
 scalar_t__ platform_init (int,char**) ; 
 int run_test_part (char*,char*) ; 
 int run_tests (int) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv) {
  if (platform_init(argc, argv))
    return EXIT_FAILURE;

  switch (argc) {
  case 1: return run_tests(1);
  case 2: return maybe_run_test(argc, argv);
  case 3: return run_test_part(argv[1], argv[2]);
  default:
    fprintf(stderr, "Too many arguments.\n");
    fflush(stderr);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}