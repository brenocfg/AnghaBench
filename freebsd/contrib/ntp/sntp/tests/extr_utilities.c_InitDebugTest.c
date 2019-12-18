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
 int /*<<< orphan*/  TEST_ASSERT_NOT_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fopen (char const*,char*) ; 
 int /*<<< orphan*/  outputFile ; 
 int outputFileOpened ; 

void
InitDebugTest(const char * filename) {
	// Clear the contents of the current file.
	// Open the output file
	outputFile = fopen(filename, "w+");
	TEST_ASSERT_NOT_NULL(outputFile);
	outputFileOpened = true;
}