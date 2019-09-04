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
typedef  int /*<<< orphan*/  git_bitvec ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_bitvec_get (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void check_some_bits(git_bitvec *bv, size_t length)
{
	size_t i;

	for (i = 0; i < length; ++i)
		cl_assert_equal_b(i % 3 == 0 || i % 7 == 0, git_bitvec_get(bv, i));
}