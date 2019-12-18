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
 int /*<<< orphan*/  print_tests (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int run_test (char*,int,int) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int maybe_run_test(int argc, char **argv) {
  if (strcmp(argv[1], "--list") == 0) {
    print_tests(stdout);
    return 0;
  }

  if (strcmp(argv[1], "spawn_helper") == 0) {
    printf("hello world\n");
    return 42;
  }

  return run_test(argv[1], 1, 1);
}