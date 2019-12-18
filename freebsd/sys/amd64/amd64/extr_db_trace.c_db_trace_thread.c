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
struct trapframe {int dummy; } ;
struct thread {int dummy; } ;
struct pcb {int /*<<< orphan*/  pcb_rsp; int /*<<< orphan*/  pcb_rip; scalar_t__ pcb_rbp; } ;
struct amd64_frame {int dummy; } ;

/* Variables and functions */
 int db_backtrace (struct thread*,struct trapframe*,struct amd64_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct trapframe* kdb_frame ; 
 struct pcb* kdb_thr_ctx (struct thread*) ; 
 struct thread* kdb_thread ; 

int
db_trace_thread(struct thread *thr, int count)
{
	struct pcb *ctx;
	struct trapframe *tf;

	ctx = kdb_thr_ctx(thr);
	tf = thr == kdb_thread ? kdb_frame : NULL;
	return (db_backtrace(thr, tf, (struct amd64_frame *)ctx->pcb_rbp,
	    ctx->pcb_rip, ctx->pcb_rsp, count));
}