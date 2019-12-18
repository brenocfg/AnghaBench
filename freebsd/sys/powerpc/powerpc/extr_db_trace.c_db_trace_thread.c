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
struct thread {int dummy; } ;
struct pcb {scalar_t__ pcb_sp; } ;
typedef  int /*<<< orphan*/  db_addr_t ;

/* Variables and functions */
 int db_backtrace (struct thread*,int /*<<< orphan*/ ,int) ; 
 struct pcb* kdb_thr_ctx (struct thread*) ; 

int
db_trace_thread(struct thread *td, int count)
{
	struct pcb *ctx;

	ctx = kdb_thr_ctx(td);
	return (db_backtrace(td, (db_addr_t)ctx->pcb_sp, count));
}