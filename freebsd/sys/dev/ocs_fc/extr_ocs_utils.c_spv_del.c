#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sparse_vector_t ;
struct TYPE_4__ {int /*<<< orphan*/  os; int /*<<< orphan*/  array; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPV_DIM ; 
 int /*<<< orphan*/  SPV_ROWLEN ; 
 int /*<<< orphan*/  _spv_del (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

void
spv_del(sparse_vector_t spv)
{
	if (spv) {
		_spv_del(spv->os, spv->array, SPV_ROWLEN, SPV_DIM);
		ocs_free(spv->os, spv, sizeof(*spv));
	}
}