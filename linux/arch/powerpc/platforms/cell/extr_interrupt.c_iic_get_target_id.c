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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  target_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_iic ; 
 TYPE_1__ per_cpu (int /*<<< orphan*/ ,int) ; 

u8 iic_get_target_id(int cpu)
{
	return per_cpu(cpu_iic, cpu).target_id;
}