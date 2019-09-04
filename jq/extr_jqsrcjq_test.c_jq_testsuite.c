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
typedef  int /*<<< orphan*/  jv ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  jv_test () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  run_jq_tests (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stdin ; 

int jq_testsuite(jv libdirs, int verbose, int argc, char* argv[]) {
  FILE *testdata = stdin;
  jv_test();
  if (argc > 0) {
    testdata = fopen(argv[0], "r");
    if (!testdata) {
      perror("fopen");
      exit(1);
    }
  }
  run_jq_tests(libdirs, verbose, testdata);
  return 0;
}