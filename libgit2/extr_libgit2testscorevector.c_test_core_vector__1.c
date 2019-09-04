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
 int /*<<< orphan*/  git_vector_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void test_core_vector__1(void)
{
	git_vector x;
	/* make initial capacity exact for our insertions. */
	git_vector_init(&x, 3, NULL);
	git_vector_insert(&x, (void*) 0xabc);
	git_vector_insert(&x, (void*) 0xdef);
	git_vector_insert(&x, (void*) 0x123);

	git_vector_remove(&x, 0); /* used to read past array bounds. */
	git_vector_free(&x);
}