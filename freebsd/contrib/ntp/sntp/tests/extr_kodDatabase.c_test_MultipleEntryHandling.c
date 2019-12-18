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
struct kod_entry {int /*<<< orphan*/  type; int /*<<< orphan*/  hostname; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_STRING (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_entry (char const*,char const*) ; 
 int /*<<< orphan*/  free (struct kod_entry*) ; 
 int /*<<< orphan*/  search_entry (char const*,struct kod_entry**) ; 

void
test_MultipleEntryHandling(void) {
	const char HOST1[] = "192.0.2.3";
	const char REASON1[] = "DENY";

	const char HOST2[] = "192.0.5.5";
	const char REASON2[] = "RATE";

	const char HOST3[] = "192.0.10.1";
	const char REASON3[] = "DENY";

	add_entry(HOST1, REASON1);
	add_entry(HOST2, REASON2);
	add_entry(HOST3, REASON3);

	struct kod_entry* result;

	TEST_ASSERT_EQUAL(1, search_entry(HOST1, &result));
	TEST_ASSERT_EQUAL_STRING(HOST1, result->hostname);
	TEST_ASSERT_EQUAL_STRING(REASON1, result->type);

	TEST_ASSERT_EQUAL(1, search_entry(HOST2, &result));
	TEST_ASSERT_EQUAL_STRING(HOST2, result->hostname);
	TEST_ASSERT_EQUAL_STRING(REASON2, result->type);

	TEST_ASSERT_EQUAL(1, search_entry(HOST3, &result));
	TEST_ASSERT_EQUAL_STRING(HOST3, result->hostname);
	TEST_ASSERT_EQUAL_STRING(REASON3, result->type);

	free(result);
}