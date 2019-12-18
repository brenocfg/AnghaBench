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
struct request_queue {int /*<<< orphan*/ * write_hints; } ;

/* Variables and functions */
 int BLK_MAX_WRITE_HINTS ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int queue_write_hint_show(void *data, struct seq_file *m)
{
	struct request_queue *q = data;
	int i;

	for (i = 0; i < BLK_MAX_WRITE_HINTS; i++)
		seq_printf(m, "hint%d: %llu\n", i, q->write_hints[i]);

	return 0;
}