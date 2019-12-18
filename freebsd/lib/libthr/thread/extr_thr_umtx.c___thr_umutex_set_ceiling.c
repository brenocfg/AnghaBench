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
typedef  int /*<<< orphan*/  uint32_t ;
struct umutex {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UMTX_OP_SET_CEILING ; 
 int _umtx_op_err (struct umutex*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
__thr_umutex_set_ceiling(struct umutex *mtx, uint32_t ceiling,
    uint32_t *oldceiling)
{

	return (_umtx_op_err(mtx, UMTX_OP_SET_CEILING, ceiling, oldceiling, 0));
}