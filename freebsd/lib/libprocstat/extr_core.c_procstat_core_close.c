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
struct procstat_core {scalar_t__ pc_magic; int /*<<< orphan*/  pc_fd; int /*<<< orphan*/  pc_elf; } ;

/* Variables and functions */
 scalar_t__ PROCSTAT_CORE_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elf_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct procstat_core*) ; 

void
procstat_core_close(struct procstat_core *core)
{

	assert(core->pc_magic == PROCSTAT_CORE_MAGIC);

	elf_end(core->pc_elf);
	close(core->pc_fd);
	free(core);
}