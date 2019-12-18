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
typedef  int /*<<< orphan*/  git_strmap ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_strmap_set (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_strmap_size (int /*<<< orphan*/ *) ; 
 char* malloc (int) ; 

__attribute__((used)) static void insert_strings(git_strmap *table, size_t count)
{
	size_t i, j, over;
	char *str;

	for (i = 0; i < count; ++i) {
		str = malloc(10);
		for (j = 0; j < 10; ++j)
			str[j] = 'a' + (i % 26);
		str[9] = '\0';

		/* if > 26, then encode larger value in first letters */
		for (j = 0, over = i / 26; over > 0; j++, over = over / 26)
			str[j] = 'A' + (over % 26);

		cl_git_pass(git_strmap_set(table, str, str));
	}

	cl_assert_equal_i(git_strmap_size(table), count);
}