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
struct TYPE_2__ {int (* cpu_setup ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ctr ; 
 TYPE_1__* model ; 
 int op_per_cpu_rc ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void op_powerpc_cpu_setup(void *dummy)
{
	int ret;

	ret = model->cpu_setup(ctr);

	if (ret != 0)
		op_per_cpu_rc = ret;
}