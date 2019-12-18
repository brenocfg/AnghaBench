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
struct seq_file {struct binder_transaction_log* private; } ;
struct binder_transaction_log {int /*<<< orphan*/ * entry; scalar_t__ full; int /*<<< orphan*/  cur; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_binder_transaction_log_entry (struct seq_file*,int /*<<< orphan*/ *) ; 

int binder_transaction_log_show(struct seq_file *m, void *unused)
{
	struct binder_transaction_log *log = m->private;
	unsigned int log_cur = atomic_read(&log->cur);
	unsigned int count;
	unsigned int cur;
	int i;

	count = log_cur + 1;
	cur = count < ARRAY_SIZE(log->entry) && !log->full ?
		0 : count % ARRAY_SIZE(log->entry);
	if (count > ARRAY_SIZE(log->entry) || log->full)
		count = ARRAY_SIZE(log->entry);
	for (i = 0; i < count; i++) {
		unsigned int index = cur++ % ARRAY_SIZE(log->entry);

		print_binder_transaction_log_entry(m, &log->entry[index]);
	}
	return 0;
}