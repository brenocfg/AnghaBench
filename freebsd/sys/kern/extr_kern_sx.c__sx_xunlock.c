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
struct sx {scalar_t__ sx_lock; int /*<<< orphan*/  sx_recurse; int /*<<< orphan*/  lock_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LOCK_LOG_LOCK (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  LOP_EXCLUSIVE ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 scalar_t__ SX_LOCK_DESTROYED ; 
 int /*<<< orphan*/  TD_LOCKS_DEC (scalar_t__) ; 
 int /*<<< orphan*/  WITNESS_UNLOCK (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  __sx_xunlock (struct sx*,scalar_t__,char const*,int) ; 
 int /*<<< orphan*/  _sx_assert (struct sx*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  _sx_xunlock_hard (struct sx*,uintptr_t,char const*,int) ; 
 scalar_t__ curthread ; 

void
_sx_xunlock(struct sx *sx, const char *file, int line)
{

	KASSERT(sx->sx_lock != SX_LOCK_DESTROYED,
	    ("sx_xunlock() of destroyed sx @ %s:%d", file, line));
	_sx_assert(sx, SA_XLOCKED, file, line);
	WITNESS_UNLOCK(&sx->lock_object, LOP_EXCLUSIVE, file, line);
	LOCK_LOG_LOCK("XUNLOCK", &sx->lock_object, 0, sx->sx_recurse, file,
	    line);
#if LOCK_DEBUG > 0
	_sx_xunlock_hard(sx, (uintptr_t)curthread, file, line);
#else
	__sx_xunlock(sx, curthread, file, line);
#endif
	TD_LOCKS_DEC(curthread);
}