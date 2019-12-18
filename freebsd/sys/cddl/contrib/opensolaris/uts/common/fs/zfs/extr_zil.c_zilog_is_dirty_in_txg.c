#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* zl_dmu_pool; } ;
typedef  TYPE_1__ zilog_t ;
typedef  int uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  dp_dirty_zilogs; } ;
typedef  TYPE_2__ dsl_pool_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int TXG_MASK ; 
 scalar_t__ txg_list_member (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

boolean_t
zilog_is_dirty_in_txg(zilog_t *zilog, uint64_t txg)
{
	dsl_pool_t *dp = zilog->zl_dmu_pool;

	if (txg_list_member(&dp->dp_dirty_zilogs, zilog, txg & TXG_MASK))
		return (B_TRUE);
	return (B_FALSE);
}