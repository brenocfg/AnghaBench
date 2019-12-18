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
struct blk_rq_stat {int /*<<< orphan*/  max; int /*<<< orphan*/  min; int /*<<< orphan*/  mean; scalar_t__ nr_samples; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void print_stat(struct seq_file *m, struct blk_rq_stat *stat)
{
	if (stat->nr_samples) {
		seq_printf(m, "samples=%d, mean=%llu, min=%llu, max=%llu",
			   stat->nr_samples, stat->mean, stat->min, stat->max);
	} else {
		seq_puts(m, "samples=0");
	}
}