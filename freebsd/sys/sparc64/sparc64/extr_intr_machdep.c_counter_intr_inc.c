#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  v_intr; } ;

/* Variables and functions */
 TYPE_1__ vm_cnt ; 
 scalar_t__ zpcpu_get (int /*<<< orphan*/ ) ; 

void
counter_intr_inc(void)
{

	*(uint64_t *)zpcpu_get(vm_cnt.v_intr) += 1;
}