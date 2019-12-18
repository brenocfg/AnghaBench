#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct seq_file {struct nitrox_device* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  dropped; int /*<<< orphan*/  completed; int /*<<< orphan*/  posted; } ;
struct nitrox_device {TYPE_1__ stats; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stats_show(struct seq_file *s, void *v)
{
	struct nitrox_device *ndev = s->private;

	seq_printf(s, "NITROX [%d] Request Statistics\n", ndev->idx);
	seq_printf(s, "  Posted: %llu\n",
		   (u64)atomic64_read(&ndev->stats.posted));
	seq_printf(s, "  Completed: %llu\n",
		   (u64)atomic64_read(&ndev->stats.completed));
	seq_printf(s, "  Dropped: %llu\n",
		   (u64)atomic64_read(&ndev->stats.dropped));

	return 0;
}