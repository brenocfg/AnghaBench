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
struct bufdomain {long bd_maxbufspace; long bd_hibufspace; long bd_bufspacethresh; int /*<<< orphan*/  bd_bufspace; } ;

/* Variables and functions */
 int ENOSPC ; 
 long atomic_fetchadd_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_subtract_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bufspace_daemon_wakeup (struct bufdomain*) ; 

__attribute__((used)) static int
bufspace_reserve(struct bufdomain *bd, int size, bool metadata)
{
	long limit, new;
	long space;

	if (metadata)
		limit = bd->bd_maxbufspace;
	else
		limit = bd->bd_hibufspace;
	space = atomic_fetchadd_long(&bd->bd_bufspace, size);
	new = space + size;
	if (new > limit) {
		atomic_subtract_long(&bd->bd_bufspace, size);
		return (ENOSPC);
	}

	/* Wake up the daemon on the transition. */
	if (space < bd->bd_bufspacethresh && new >= bd->bd_bufspacethresh)
		bufspace_daemon_wakeup(bd);

	return (0);
}