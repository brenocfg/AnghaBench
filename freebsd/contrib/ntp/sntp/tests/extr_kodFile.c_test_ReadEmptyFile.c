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
 int /*<<< orphan*/  CreatePath (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INPUT_DIR ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  kod_db_cnt ; 
 int /*<<< orphan*/  kod_init_kod_db (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
test_ReadEmptyFile(void) {
	kod_init_kod_db(CreatePath("kod-test-empty", INPUT_DIR), TRUE);

	TEST_ASSERT_EQUAL(0, kod_db_cnt);
}