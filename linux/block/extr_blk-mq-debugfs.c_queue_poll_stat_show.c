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
struct request_queue {int /*<<< orphan*/ * poll_stat; } ;

/* Variables and functions */
 int BLK_MQ_POLL_STATS_BKTS ; 
 int /*<<< orphan*/  print_stat (struct seq_file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int queue_poll_stat_show(void *data, struct seq_file *m)
{
	struct request_queue *q = data;
	int bucket;

	for (bucket = 0; bucket < (BLK_MQ_POLL_STATS_BKTS / 2); bucket++) {
		seq_printf(m, "read  (%d Bytes): ", 1 << (9 + bucket));
		print_stat(m, &q->poll_stat[2 * bucket]);
		seq_puts(m, "\n");

		seq_printf(m, "write (%d Bytes): ",  1 << (9 + bucket));
		print_stat(m, &q->poll_stat[2 * bucket + 1]);
		seq_puts(m, "\n");
	}
	return 0;
}