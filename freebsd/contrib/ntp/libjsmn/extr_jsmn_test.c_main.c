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
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  test (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_array_nomem ; 
 int /*<<< orphan*/  test_count ; 
 int /*<<< orphan*/  test_empty ; 
 int test_failed ; 
 int /*<<< orphan*/  test_input_length ; 
 int /*<<< orphan*/  test_issue_22 ; 
 int /*<<< orphan*/  test_keyvalue ; 
 int /*<<< orphan*/  test_nonstrict ; 
 int /*<<< orphan*/  test_objects_arrays ; 
 int /*<<< orphan*/  test_partial_array ; 
 int /*<<< orphan*/  test_partial_string ; 
 int test_passed ; 
 int /*<<< orphan*/  test_primitive ; 
 int /*<<< orphan*/  test_simple ; 
 int /*<<< orphan*/  test_string ; 
 int /*<<< orphan*/  test_unicode_characters ; 
 int /*<<< orphan*/  test_unquoted_keys ; 

int main() {
	test(test_empty, "general test for a empty JSON objects/arrays");
	test(test_simple, "general test for a simple JSON string");
	test(test_primitive, "test primitive JSON data types");
	test(test_string, "test string JSON data types");
	test(test_partial_string, "test partial JSON string parsing");
	test(test_partial_array, "test partial array reading");
	test(test_array_nomem, "test array reading with a smaller number of tokens");
	test(test_unquoted_keys, "test unquoted keys (like in JavaScript)");
	test(test_objects_arrays, "test objects and arrays");
	test(test_unicode_characters, "test unicode characters");
	test(test_input_length, "test strings that are not null-terminated");
	test(test_issue_22, "test issue #22");
	test(test_count, "test tokens count estimation");
	test(test_nonstrict, "test for non-strict mode");
	test(test_keyvalue, "test for keys/values");
	printf("\nPASSED: %d\nFAILED: %d\n", test_passed, test_failed);
	return 0;
}