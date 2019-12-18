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
typedef  int /*<<< orphan*/  register_t ;
struct TYPE_2__ {int /*<<< orphan*/  tf_pc; } ;

/* Variables and functions */
#define  GDB_REG_PC 128 
 int /*<<< orphan*/  curthread ; 
 TYPE_1__* kdb_frame ; 
 int /*<<< orphan*/  kdb_thread ; 

void
gdb_cpu_setreg(int regnum, void *val)
{

	switch (regnum) {
	case GDB_REG_PC:
		if (kdb_thread  == curthread)
			kdb_frame->tf_pc = *(register_t *)val;
	}
}