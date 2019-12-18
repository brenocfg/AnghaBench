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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  append_unsigned_native (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  cur_vcpu ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  finish_packet () ; 
 int /*<<< orphan*/ * gdb_regset ; 
 int /*<<< orphan*/ * gdb_regsize ; 
 int nitems (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_packet () ; 
 int vm_get_register_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gdb_read_regs(void)
{
	uint64_t regvals[nitems(gdb_regset)];
	int i;

	if (vm_get_register_set(ctx, cur_vcpu, nitems(gdb_regset),
	    gdb_regset, regvals) == -1) {
		send_error(errno);
		return;
	}
	start_packet();
	for (i = 0; i < nitems(regvals); i++)
		append_unsigned_native(regvals[i], gdb_regsize[i]);
	finish_packet();
}