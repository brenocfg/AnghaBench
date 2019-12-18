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
struct wakeup_source {int dummy; } ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_wakeup_source_stats (struct seq_file*,struct wakeup_source*) ; 

__attribute__((used)) static int wakeup_sources_stats_seq_show(struct seq_file *m, void *v)
{
	struct wakeup_source *ws = v;

	print_wakeup_source_stats(m, ws);

	return 0;
}