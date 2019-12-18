#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ uint8_t ;
struct TYPE_8__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_2__ ocs_hw_t ;
typedef  TYPE_1__ ocs_hw_set_nvparms_cb_arg_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
ocs_hw_set_nvparms_cb(ocs_hw_t *hw, int32_t status, uint8_t *mqe, void *arg)
{
	ocs_hw_set_nvparms_cb_arg_t *cb_arg = arg;

	if (cb_arg->cb) {
		cb_arg->cb(status, cb_arg->arg);
	}

	ocs_free(hw->os, mqe, SLI4_BMBX_SIZE);
	ocs_free(hw->os, cb_arg, sizeof(ocs_hw_set_nvparms_cb_arg_t));

	return 0;
}