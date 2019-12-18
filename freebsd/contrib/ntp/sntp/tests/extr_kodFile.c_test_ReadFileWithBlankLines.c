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
struct kod_entry {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  hostname; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CreatePath (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INPUT_DIR ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_STRING (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  kod_db_cnt ; 
 int /*<<< orphan*/  kod_init_kod_db (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  search_entry (char*,struct kod_entry**) ; 

void
test_ReadFileWithBlankLines(void) {
	kod_init_kod_db(CreatePath("kod-test-blanks", INPUT_DIR), TRUE);

	TEST_ASSERT_EQUAL(3, kod_db_cnt);

	struct kod_entry* res;

	TEST_ASSERT_EQUAL(1, search_entry("192.0.2.5", &res));
	TEST_ASSERT_EQUAL_STRING("DENY", res->type);
	TEST_ASSERT_EQUAL_STRING("192.0.2.5", res->hostname);
	TEST_ASSERT_EQUAL(0x12345678, res->timestamp);

	TEST_ASSERT_EQUAL(1, search_entry("192.0.2.100", &res));
	TEST_ASSERT_EQUAL_STRING("RSTR", res->type);
	TEST_ASSERT_EQUAL_STRING("192.0.2.100", res->hostname);
	TEST_ASSERT_EQUAL(0xfff, res->timestamp);

	TEST_ASSERT_EQUAL(1, search_entry("example.com", &res));
	TEST_ASSERT_EQUAL_STRING("DENY", res->type);
	TEST_ASSERT_EQUAL_STRING("example.com", res->hostname);
	TEST_ASSERT_EQUAL(0xabcd, res->timestamp);
}