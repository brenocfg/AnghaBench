#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  void pool_hdr_t ;
struct TYPE_3__ {int /*<<< orphan*/  a; } ;
typedef  TYPE_1__ ocs_pool_t ;

/* Variables and functions */
 void* ocs_array_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *
ocs_pool_get_instance(ocs_pool_t *pool, uint32_t idx)
{
	pool_hdr_t *h = ocs_array_get(pool->a, idx);

	if (h == NULL) {
		return NULL;
	}
	return &h[1];
}