#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int timestamp; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CompareFileContent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreatePath (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetFileSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INPUT_DIR ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ASSERT_TRUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_entry (char*,char*) ; 
 int /*<<< orphan*/  estrdup (char*) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__** kod_db ; 
 int /*<<< orphan*/  kod_db_file ; 
 int /*<<< orphan*/  write_kod_db () ; 

void
test_WriteFileWithSingleEntry(void) {
	kod_db_file = estrdup("kod-output-single"); 
	add_entry("host1", "DENY");

	// Here we must manipulate the timestamps, so they match the one in
	// the expected file.

	kod_db[0]->timestamp = 1;

	write_kod_db();

	// Open file and compare sizes.
	FILE * actual = fopen(kod_db_file, "rb");
	FILE * expected = fopen(CreatePath("kod-expected-single", INPUT_DIR),"rb");

	TEST_ASSERT_NOT_NULL(actual);
	TEST_ASSERT_NOT_NULL(expected);

	TEST_ASSERT_EQUAL(GetFileSize(expected), GetFileSize(actual));
	
	TEST_ASSERT_TRUE(CompareFileContent(expected, actual));
}