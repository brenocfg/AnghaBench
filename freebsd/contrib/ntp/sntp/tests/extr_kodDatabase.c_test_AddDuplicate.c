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
struct kod_entry {scalar_t__ timestamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_FALSE (int) ; 
 int /*<<< orphan*/  add_entry (char const*,char const*) ; 
 int /*<<< orphan*/  free (struct kod_entry*) ; 
 int /*<<< orphan*/  search_entry (char const*,struct kod_entry**) ; 
 int /*<<< orphan*/  sleep (int) ; 

void
test_AddDuplicate(void) {
	const char HOST[] = "192.0.2.3";
	const char REASON1[] = "RATE";
	const char REASON2[] = "DENY";

	add_entry(HOST, REASON1);
	struct kod_entry* result1;
	TEST_ASSERT_EQUAL(1, search_entry(HOST, &result1));

	/* 
	 * Sleeps for two seconds since we want to ensure that
	 * the timestamp is updated to a new value.
	 */
	sleep(2);

	add_entry(HOST, REASON2);
	struct kod_entry* result2;
	TEST_ASSERT_EQUAL(1, search_entry(HOST, &result2));

	TEST_ASSERT_FALSE(result1->timestamp == result2->timestamp);

	free(result1);
	free(result2);
}