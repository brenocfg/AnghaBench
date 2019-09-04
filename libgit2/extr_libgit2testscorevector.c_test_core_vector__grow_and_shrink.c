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
typedef  int /*<<< orphan*/  git_vector ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (void**) ; 
 int /*<<< orphan*/  GIT_VECTOR_INIT ; 
 int /*<<< orphan*/  assert_vector (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_insert (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  git_vector_insert_null (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  git_vector_remove_range (int /*<<< orphan*/ *,int,int) ; 

void test_core_vector__grow_and_shrink(void)
{
	git_vector x = GIT_VECTOR_INIT;
	void *expected1[] = {
		(void *)0x02, (void *)0x03, (void *)0x04, (void *)0x05,
		(void *)0x06, (void *)0x07, (void *)0x08, (void *)0x09,
		(void *)0x0a
	};
	void *expected2[] = {
		(void *)0x02, (void *)0x04, (void *)0x05, (void *)0x06,
		(void *)0x07, (void *)0x08, (void *)0x09, (void *)0x0a
	};
	void *expected3[] = {
		(void *)0x02, (void *)0x04, (void *)0x05, (void *)0x06,
		(void *)0x0a
	};
	void *expected4[] = {
		(void *)0x02, (void *)0x04, (void *)0x05
	};
	void *expected5[] = {
		(void *)0x00, (void *)0x00, (void *)0x02, (void *)0x04,
		(void *)0x05
	};
	void *expected6[] = {
		(void *)0x00, (void *)0x00, (void *)0x02, (void *)0x04,
		(void *)0x05, (void *)0x00
	};
	void *expected7[] = {
		(void *)0x00, (void *)0x00, (void *)0x02, (void *)0x04,
		(void *)0x00, (void *)0x00, (void *)0x00, (void *)0x05,
		(void *)0x00
	};
	void *expected8[] = {
		(void *)0x04, (void *)0x00, (void *)0x00, (void *)0x00,
		(void *)0x05, (void *)0x00
	};
	void *expected9[] = {
		(void *)0x04, (void *)0x00, (void *)0x05, (void *)0x00
	};
	void *expectedA[] = { (void *)0x04, (void *)0x00 };
	void *expectedB[] = { (void *)0x04 };

	git_vector_insert(&x, (void *)0x01);
	git_vector_insert(&x, (void *)0x02);
	git_vector_insert(&x, (void *)0x03);
	git_vector_insert(&x, (void *)0x04);
	git_vector_insert(&x, (void *)0x05);
	git_vector_insert(&x, (void *)0x06);
	git_vector_insert(&x, (void *)0x07);
	git_vector_insert(&x, (void *)0x08);
	git_vector_insert(&x, (void *)0x09);
	git_vector_insert(&x, (void *)0x0a);

	git_vector_remove_range(&x, 0, 1);
	assert_vector(&x, expected1, ARRAY_SIZE(expected1));

	git_vector_remove_range(&x, 1, 1);
	assert_vector(&x, expected2, ARRAY_SIZE(expected2));

	git_vector_remove_range(&x, 4, 3);
	assert_vector(&x, expected3, ARRAY_SIZE(expected3));

	git_vector_remove_range(&x, 3, 2);
	assert_vector(&x, expected4, ARRAY_SIZE(expected4));

	git_vector_insert_null(&x, 0, 2);
	assert_vector(&x, expected5, ARRAY_SIZE(expected5));

	git_vector_insert_null(&x, 5, 1);
	assert_vector(&x, expected6, ARRAY_SIZE(expected6));

	git_vector_insert_null(&x, 4, 3);
	assert_vector(&x, expected7, ARRAY_SIZE(expected7));

	git_vector_remove_range(&x, 0, 3);
	assert_vector(&x, expected8, ARRAY_SIZE(expected8));

	git_vector_remove_range(&x, 1, 2);
	assert_vector(&x, expected9, ARRAY_SIZE(expected9));

	git_vector_remove_range(&x, 2, 2);
	assert_vector(&x, expectedA, ARRAY_SIZE(expectedA));

	git_vector_remove_range(&x, 1, 1);
	assert_vector(&x, expectedB, ARRAY_SIZE(expectedB));

	git_vector_remove_range(&x, 0, 1);
	assert_vector(&x, NULL, 0);

	git_vector_free(&x);
}