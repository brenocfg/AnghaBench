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
struct seq_file {int dummy; } ;
struct binder_transaction_log_entry {int call_type; int /*<<< orphan*/  debug_id_done; int /*<<< orphan*/  return_error_line; int /*<<< orphan*/  return_error_param; int /*<<< orphan*/  return_error; int /*<<< orphan*/  offsets_size; int /*<<< orphan*/  data_size; int /*<<< orphan*/  target_handle; int /*<<< orphan*/  to_node; int /*<<< orphan*/  context_name; int /*<<< orphan*/  to_thread; int /*<<< orphan*/  to_proc; int /*<<< orphan*/  from_thread; int /*<<< orphan*/  from_proc; int /*<<< orphan*/  debug_id; } ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static void print_binder_transaction_log_entry(struct seq_file *m,
					struct binder_transaction_log_entry *e)
{
	int debug_id = READ_ONCE(e->debug_id_done);
	/*
	 * read barrier to guarantee debug_id_done read before
	 * we print the log values
	 */
	smp_rmb();
	seq_printf(m,
		   "%d: %s from %d:%d to %d:%d context %s node %d handle %d size %d:%d ret %d/%d l=%d",
		   e->debug_id, (e->call_type == 2) ? "reply" :
		   ((e->call_type == 1) ? "async" : "call "), e->from_proc,
		   e->from_thread, e->to_proc, e->to_thread, e->context_name,
		   e->to_node, e->target_handle, e->data_size, e->offsets_size,
		   e->return_error, e->return_error_param,
		   e->return_error_line);
	/*
	 * read-barrier to guarantee read of debug_id_done after
	 * done printing the fields of the entry
	 */
	smp_rmb();
	seq_printf(m, debug_id && debug_id == READ_ONCE(e->debug_id_done) ?
			"\n" : " (incomplete)\n");
}