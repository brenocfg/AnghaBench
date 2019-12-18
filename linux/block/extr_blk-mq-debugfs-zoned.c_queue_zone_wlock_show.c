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
struct request_queue {unsigned int nr_zones; int /*<<< orphan*/  seq_zones_wlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned int) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ ) ; 

int queue_zone_wlock_show(void *data, struct seq_file *m)
{
	struct request_queue *q = data;
	unsigned int i;

	if (!q->seq_zones_wlock)
		return 0;

	for (i = 0; i < q->nr_zones; i++)
		if (test_bit(i, q->seq_zones_wlock))
			seq_printf(m, "%u\n", i);

	return 0;
}