#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void ucl_object_t ;
struct TYPE_4__ {int n; int /*<<< orphan*/ * a; } ;
struct TYPE_5__ {TYPE_1__ ar; } ;
typedef  TYPE_2__ ucl_hash_t ;
typedef  struct ucl_hash_real_iter* ucl_hash_iter_t ;
struct ucl_hash_real_iter {int /*<<< orphan*/ * cur; int /*<<< orphan*/ * end; } ;

/* Variables and functions */
 struct ucl_hash_real_iter* UCL_ALLOC (int) ; 
 int /*<<< orphan*/  UCL_FREE (int,struct ucl_hash_real_iter*) ; 

const void*
ucl_hash_iterate (ucl_hash_t *hashlin, ucl_hash_iter_t *iter)
{
	struct ucl_hash_real_iter *it = (struct ucl_hash_real_iter *)(*iter);
	const ucl_object_t *ret = NULL;

	if (hashlin == NULL) {
		return NULL;
	}

	if (it == NULL) {
		it = UCL_ALLOC (sizeof (*it));

		if (it == NULL) {
			return NULL;
		}

		it->cur = &hashlin->ar.a[0];
		it->end = it->cur + hashlin->ar.n;
	}

	if (it->cur < it->end) {
		ret = *it->cur++;
	}
	else {
		UCL_FREE (sizeof (*it), it);
		*iter = NULL;
		return NULL;
	}

	*iter = it;

	return ret;
}