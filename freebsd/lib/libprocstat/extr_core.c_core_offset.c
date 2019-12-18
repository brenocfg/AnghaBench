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
struct procstat_core {scalar_t__ pc_magic; int /*<<< orphan*/  pc_fd; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 scalar_t__ PROCSTAT_CORE_MAGIC ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int) ; 
 int lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
core_offset(struct procstat_core *core, off_t offset)
{

	assert(core->pc_magic == PROCSTAT_CORE_MAGIC);

	if (lseek(core->pc_fd, offset, SEEK_SET) == -1) {
		warn("core: lseek(%jd)", (intmax_t)offset);
		return (false);
	}
	return (true);
}