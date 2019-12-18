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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {TYPE_1__* qtop; } ;
typedef  TYPE_2__ ocs_hw_t ;
struct TYPE_4__ {int /*<<< orphan*/ * entry_counts; } ;

/* Variables and functions */
 size_t QTOP_EQ ; 

uint32_t
ocs_hw_qtop_eq_count(ocs_hw_t *hw)
{
	return hw->qtop->entry_counts[QTOP_EQ];
}