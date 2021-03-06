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
 int /*<<< orphan*/  git_vector_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_insert (int /*<<< orphan*/ *,void*) ; 

void test_core_vector__0(void)
{
	git_vector x;
	int i;
	git_vector_init(&x, 1, NULL);
	for (i = 0; i < 10; ++i) {
		git_vector_insert(&x, (void*) 0xabc);
	}
	git_vector_free(&x);
}