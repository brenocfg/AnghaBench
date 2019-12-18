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
 int /*<<< orphan*/  search_entry (char const*,struct kod_entry**) ; 

void
test_SingleEntryHandling(void) {
	const char HOST[] = "192.0.2.5";
	const char REASON[] = "DENY";

	add_entry(HOST, REASON);

	struct kod_entry* result;

	TEST_ASSERT_EQUAL(1, search_entry(HOST, &result));
	TEST_ASSERT_EQUAL_STRING(HOST, result->hostname);
	TEST_ASSERT_EQUAL_STRING(REASON, result->type);
}