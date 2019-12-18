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
struct lockf_entry {scalar_t__ lf_start; scalar_t__ lf_end; TYPE_1__* lf_owner; int /*<<< orphan*/  lf_type; } ;
struct lockf {int dummy; } ;
struct flock {scalar_t__ l_start; scalar_t__ l_len; int /*<<< orphan*/  l_type; int /*<<< orphan*/  l_sysid; int /*<<< orphan*/  l_pid; int /*<<< orphan*/  l_whence; } ;
struct TYPE_2__ {int /*<<< orphan*/  lo_sysid; int /*<<< orphan*/  lo_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_UNLCK ; 
 scalar_t__ OFF_MAX ; 
 int /*<<< orphan*/  SEEK_SET ; 
 struct lockf_entry* lf_getblock (struct lockf*,struct lockf_entry*) ; 
 int /*<<< orphan*/  lf_print (char*,struct lockf_entry*) ; 
 int lockf_debug ; 

__attribute__((used)) static int
lf_getlock(struct lockf *state, struct lockf_entry *lock, struct flock *fl)
{
	struct lockf_entry *block;

#ifdef LOCKF_DEBUG
	if (lockf_debug & 1)
		lf_print("lf_getlock", lock);
#endif /* LOCKF_DEBUG */

	if ((block = lf_getblock(state, lock))) {
		fl->l_type = block->lf_type;
		fl->l_whence = SEEK_SET;
		fl->l_start = block->lf_start;
		if (block->lf_end == OFF_MAX)
			fl->l_len = 0;
		else
			fl->l_len = block->lf_end - block->lf_start + 1;
		fl->l_pid = block->lf_owner->lo_pid;
		fl->l_sysid = block->lf_owner->lo_sysid;
	} else {
		fl->l_type = F_UNLCK;
	}
	return (0);
}