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
struct kinfo_proc {int /*<<< orphan*/  ki_comm; int /*<<< orphan*/  ki_tid; int /*<<< orphan*/  ki_pid; } ;

/* Variables and functions */
 int PS_OPT_PERTHREAD ; 
 int procstat_opts ; 
 int /*<<< orphan*/  xo_emit (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_prefix(struct kinfo_proc *kipp)
{

	xo_emit("{d:process_id/%5d/%d} ", kipp->ki_pid);
	if ((procstat_opts & PS_OPT_PERTHREAD) != 0)
		xo_emit("{d:thread_id/%6d/%d} ", kipp->ki_tid);
	xo_emit("{d:command/%-16s/%s} ", kipp->ki_comm);
}