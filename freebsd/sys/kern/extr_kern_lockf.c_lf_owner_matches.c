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
struct lock_owner {scalar_t__ lo_pid; scalar_t__ lo_sysid; scalar_t__ lo_id; } ;
struct flock {scalar_t__ l_pid; scalar_t__ l_sysid; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int F_REMOTE ; 

__attribute__((used)) static int
lf_owner_matches(struct lock_owner *lo, caddr_t id, struct flock *fl,
    int flags)
{
	if (flags & F_REMOTE) {
		return lo->lo_pid == fl->l_pid
			&& lo->lo_sysid == fl->l_sysid;
	} else {
		return lo->lo_id == id;
	}
}