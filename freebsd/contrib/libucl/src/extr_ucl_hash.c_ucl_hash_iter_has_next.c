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
typedef  int /*<<< orphan*/  ucl_hash_t ;
typedef  scalar_t__ ucl_hash_iter_t ;
struct ucl_hash_real_iter {int cur; int end; } ;

/* Variables and functions */

bool
ucl_hash_iter_has_next (ucl_hash_t *hashlin, ucl_hash_iter_t iter)
{
	struct ucl_hash_real_iter *it = (struct ucl_hash_real_iter *)(iter);

	return it->cur < it->end - 1;
}