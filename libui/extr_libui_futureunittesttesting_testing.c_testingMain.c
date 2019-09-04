#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* name; scalar_t__ skipped; scalar_t__ failed; int /*<<< orphan*/  (* f ) (TYPE_1__*) ;int /*<<< orphan*/  returnNowBuf; struct TYPE_5__* next; } ;
typedef  TYPE_1__ testingT ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  runDefers (TYPE_1__*) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 TYPE_1__* tests ; 

int testingMain(void)
{
	testingT *t;
	int anyFailed;
	const char *status;

	// TODO see if this should run if all tests are skipped
	if (tests == NULL) {
		fprintf(stderr, "warning: no tests to run\n");
		// imitate Go here (TODO confirm this)
		return 0;
	}

	anyFailed = 0;
	for (t = tests; t != NULL; t = t->next) {
		printf("=== RUN   %s\n", t->name);
		if (setjmp(t->returnNowBuf) == 0)
			(*(t->f))(t);
		runDefers(t);
		status = "PASS";
		if (t->failed) {
			status = "FAIL";
			anyFailed = 1;
		} else if (t->skipped)
			// note that failed overrides skipped
			status = "SKIP";
		printf("--- %s: %s (%s)\n", status, t->name, "TODO");
	}

	if (anyFailed) {
		printf("FAIL\n");
		return 1;
	}
	printf("PASS\n");
	return 0;
}