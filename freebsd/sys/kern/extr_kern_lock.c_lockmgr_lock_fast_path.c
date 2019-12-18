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
typedef  int u_int ;
struct lock_object {int dummy; } ;
struct lock_class {int /*<<< orphan*/  (* lc_unlock ) (struct lock_object*) ;} ;
struct TYPE_2__ {int lo_flags; } ;
struct lock {int /*<<< orphan*/  lk_lock; TYPE_1__ lock_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  LK_CAN_WITNESS (int) ; 
#define  LK_EXCLUSIVE 131 
 int LK_INTERLOCK ; 
 int LK_NOSHARE ; 
 int /*<<< orphan*/  LK_PRIO_DEFAULT ; 
#define  LK_SHARED 130 
 int /*<<< orphan*/  LK_TIMO_DEFAULT ; 
#define  LK_TRYUPGRADE 129 
 int LK_TYPE_MASK ; 
 int /*<<< orphan*/  LK_UNLOCKED ; 
#define  LK_UPGRADE 128 
 int /*<<< orphan*/  LK_WMESG_DEFAULT ; 
 struct lock_class* LOCK_CLASS (struct lock_object*) ; 
 int LOP_EXCLUSIVE ; 
 int LOP_NEWORDER ; 
 int /*<<< orphan*/  WITNESS_CHECKORDER (TYPE_1__*,int,char const*,int,struct lock_object*) ; 
 int __lockmgr_args (struct lock*,int,struct lock_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ __predict_false (int) ; 
 scalar_t__ __predict_true (int) ; 
 int /*<<< orphan*/  atomic_cmpset_acq_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,uintptr_t) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  lockmgr_note_exclusive_acquire (struct lock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int) ; 
 int /*<<< orphan*/  lockmgr_note_shared_acquire (struct lock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int) ; 
 int lockmgr_slock_hard (struct lock*,int,struct lock_object*,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockmgr_slock_try (struct lock*,uintptr_t*,int,int) ; 
 int lockmgr_upgrade (struct lock*,int,struct lock_object*,char const*,int,int /*<<< orphan*/ *) ; 
 int lockmgr_xlock_hard (struct lock*,int,struct lock_object*,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * panicstr ; 
 int /*<<< orphan*/  stub1 (struct lock_object*) ; 

int
lockmgr_lock_fast_path(struct lock *lk, u_int flags, struct lock_object *ilk,
    const char *file, int line)
{
	struct lock_class *class;
	uintptr_t x, tid;
	u_int op;
	bool locked;

	if (__predict_false(panicstr != NULL))
		return (0);

	op = flags & LK_TYPE_MASK;
	locked = false;
	switch (op) {
	case LK_SHARED:
		if (LK_CAN_WITNESS(flags))
			WITNESS_CHECKORDER(&lk->lock_object, LOP_NEWORDER,
			    file, line, flags & LK_INTERLOCK ? ilk : NULL);
		if (__predict_false(lk->lock_object.lo_flags & LK_NOSHARE))
			break;
		if (lockmgr_slock_try(lk, &x, flags, true)) {
			lockmgr_note_shared_acquire(lk, 0, 0,
			    file, line, flags);
			locked = true;
		} else {
			return (lockmgr_slock_hard(lk, flags, ilk, file, line,
			    NULL));
		}
		break;
	case LK_EXCLUSIVE:
		if (LK_CAN_WITNESS(flags))
			WITNESS_CHECKORDER(&lk->lock_object, LOP_NEWORDER |
			    LOP_EXCLUSIVE, file, line, flags & LK_INTERLOCK ?
			    ilk : NULL);
		tid = (uintptr_t)curthread;
		if (lk->lk_lock == LK_UNLOCKED &&
		    atomic_cmpset_acq_ptr(&lk->lk_lock, LK_UNLOCKED, tid)) {
			lockmgr_note_exclusive_acquire(lk, 0, 0, file, line,
			    flags);
			locked = true;
		} else {
			return (lockmgr_xlock_hard(lk, flags, ilk, file, line,
			    NULL));
		}
		break;
	case LK_UPGRADE:
	case LK_TRYUPGRADE:
		return (lockmgr_upgrade(lk, flags, ilk, file, line, NULL));
	default:
		break;
	}
	if (__predict_true(locked)) {
		if (__predict_false(flags & LK_INTERLOCK)) {
			class = LOCK_CLASS(ilk);
			class->lc_unlock(ilk);
		}
		return (0);
	} else {
		return (__lockmgr_args(lk, flags, ilk, LK_WMESG_DEFAULT,
		    LK_PRIO_DEFAULT, LK_TIMO_DEFAULT, file, line));
	}
}