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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ eq_count; } ;
typedef  TYPE_1__ ocs_hw_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_hw_process (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
ocs_hw_flush(ocs_hw_t *hw)
{
	uint32_t	i = 0;

	/* Process any remaining completions */
	for (i = 0; i < hw->eq_count; i++) {
		ocs_hw_process(hw, i, ~0);
	}

	return 0;
}