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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CompareFileContent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  outputFile ; 
 scalar_t__ outputFileOpened ; 

void
FinishDebugTest(const char * expected,
		     const char * actual) {
	if (outputFileOpened)
		fclose(outputFile);

	FILE * e = fopen(expected,"rb");
	FILE * a = fopen(actual,"rb");
	TEST_ASSERT_NOT_NULL(e);
	TEST_ASSERT_NOT_NULL(a);

	CompareFileContent(e, a);
}