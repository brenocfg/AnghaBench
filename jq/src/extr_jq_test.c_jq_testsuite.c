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
 int atoi (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  jv_test () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  run_jq_tests (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int jq_testsuite(jv libdirs, int verbose, int argc, char* argv[]) {
  FILE *testdata = stdin;
  int skip = -1;
  int take = -1;
  jv_test();
  if (argc > 0) {
    for(int i = 0; i < argc; i++) {
      if (!strcmp(argv[i], "--skip")) {
        skip = atoi(argv[i+1]);
        i++;
      } else if (!strcmp(argv[i], "--take")) {
        take = atoi(argv[i+1]);
        i++;
      } else {
        testdata = fopen(argv[i], "r");
        if (!testdata) {
          perror("fopen");
          exit(1);
        }
      }
    }
  }
  run_jq_tests(libdirs, verbose, testdata, skip, take);
  return 0;
}