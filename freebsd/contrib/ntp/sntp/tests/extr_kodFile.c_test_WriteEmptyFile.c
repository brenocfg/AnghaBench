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
 int /*<<< orphan*/  GetFileSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  estrdup (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kod_db_file ; 
 int /*<<< orphan*/  write_kod_db () ; 

void
test_WriteEmptyFile(void) {
	kod_db_file = estrdup("kod-output-blank");
	write_kod_db();

	// Open file and ensure that the filesize is 0 bytes.
	FILE * is = fopen(kod_db_file, "rb");
	TEST_ASSERT_NOT_NULL(is);

	TEST_ASSERT_EQUAL(0, GetFileSize(is));

	fclose(is);
}