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
struct smb_connobj {int co_level; int co_usecount; int /*<<< orphan*/  co_interlock; int /*<<< orphan*/ * co_locker; scalar_t__ co_lockcnt; int /*<<< orphan*/  co_lock; int /*<<< orphan*/  co_children; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SX_RECURSE ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  smb_co_lock (struct smb_connobj*) ; 
 int /*<<< orphan*/  sx_init_flags (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
smb_co_init(struct smb_connobj *cp, int level, char *ilockname, char *lockname)
{
	SLIST_INIT(&cp->co_children);
	sx_init_flags(&cp->co_interlock, ilockname, SX_RECURSE);
	cv_init(&cp->co_lock, "smblock");
	cp->co_lockcnt = 0;
	cp->co_locker = NULL;
	cp->co_level = level;
	cp->co_usecount = 1;
	sx_xlock(&cp->co_interlock);
	smb_co_lock(cp);
	sx_unlock(&cp->co_interlock);
}