#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_4__ {TYPE_1__* mm; } ;
struct TYPE_3__ {int /*<<< orphan*/  mmap_sem; scalar_t__ pgd; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptdump_walk_pgd_level_debugfs (struct seq_file*,scalar_t__,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ptdump_curknl_show(struct seq_file *m, void *v)
{
	if (current->mm->pgd) {
		down_read(&current->mm->mmap_sem);
		ptdump_walk_pgd_level_debugfs(m, current->mm->pgd, false);
		up_read(&current->mm->mmap_sem);
	}
	return 0;
}