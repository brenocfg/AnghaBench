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
struct kod_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_TRUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_entry (char const*,char const*) ; 
 int /*<<< orphan*/  search_entry (char const*,struct kod_entry**) ; 

void
test_NoMatchInSearch(void) {
	const char HOST_ADD[] = "192.0.2.6";
	const char HOST_NOTADD[] = "192.0.6.1";
	const char REASON[] = "DENY";

	add_entry(HOST_ADD, REASON);

	struct kod_entry* result;

	TEST_ASSERT_EQUAL(0, search_entry(HOST_NOTADD, &result));
	TEST_ASSERT_TRUE(result == NULL);
}