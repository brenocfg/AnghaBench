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
struct key {int dummy; } ;

/* Variables and functions */
 char* CreatePath (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyPath (char const*) ; 
 int /*<<< orphan*/  INPUT_DIR ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_NULL (char const*) ; 
 int /*<<< orphan*/  TEST_ASSERT_NULL (struct key*) ; 
 int /*<<< orphan*/  auth_init (char const*,struct key**) ; 

void
test_ReadEmptyKeyFile(void)
{
	struct key *	keys = NULL;
	const char *	path = CreatePath("key-test-empty", INPUT_DIR);

	TEST_ASSERT_NOT_NULL(path);
	TEST_ASSERT_EQUAL(0, auth_init(path, &keys));
	TEST_ASSERT_NULL(keys);

	DestroyPath(path);
}