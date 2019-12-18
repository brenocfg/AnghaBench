#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  os; int /*<<< orphan*/ * fcf_index_fcfi; } ;
typedef  TYPE_1__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_domain_t ;

/* Variables and functions */
 size_t SLI4_MAX_FCF_INDEX ; 
 int /*<<< orphan*/ * ocs_hw_domain_get (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,size_t,size_t) ; 

__attribute__((used)) static ocs_domain_t *
ocs_hw_domain_get_indexed(ocs_hw_t *hw, uint16_t fcf_index)
{

	if (hw == NULL) {
		ocs_log_err(NULL, "bad parameter hw=%p\n", hw);
		return NULL;
	}

	if (fcf_index < SLI4_MAX_FCF_INDEX) {
		return ocs_hw_domain_get(hw, hw->fcf_index_fcfi[fcf_index]);
	} else {
		ocs_log_test(hw->os, "FCF index %d out of range (max %d)\n",
			     fcf_index, SLI4_MAX_FCF_INDEX);
		return NULL;
	}
}