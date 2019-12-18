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
struct seq_file {int* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wakeup_srcu ; 

__attribute__((used)) static void wakeup_sources_stats_seq_stop(struct seq_file *m, void *v)
{
	int *srcuidx = m->private;

	srcu_read_unlock(&wakeup_srcu, *srcuidx);
}