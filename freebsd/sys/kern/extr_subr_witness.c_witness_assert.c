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
struct lock_object {int lo_name; int /*<<< orphan*/ * lo_witness; } ;
struct lock_instance {int li_flags; } ;
struct lock_class {int lc_flags; int /*<<< orphan*/  lc_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  td_sleeplocks; } ;

/* Variables and functions */
#define  LA_LOCKED 131 
 int const LA_NOTRECURSED ; 
 int const LA_RECURSED ; 
#define  LA_SLOCKED 130 
#define  LA_UNLOCKED 129 
#define  LA_XLOCKED 128 
 int LC_SLEEPLOCK ; 
 int LC_SPINLOCK ; 
 int LI_EXCLUSIVE ; 
 int LI_RECURSEMASK ; 
 struct lock_class* LOCK_CLASS (struct lock_object const*) ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 TYPE_1__* curthread ; 
 struct lock_instance* find_instance (int /*<<< orphan*/ ,struct lock_object const*) ; 
 int /*<<< orphan*/  fixup_filename (char const*) ; 
 int /*<<< orphan*/  kassert_panic (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/ * panicstr ; 
 int /*<<< orphan*/  spinlocks ; 
 int witness_watch ; 

void
witness_assert(const struct lock_object *lock, int flags, const char *file,
    int line)
{
#ifdef INVARIANT_SUPPORT
	struct lock_instance *instance;
	struct lock_class *class;

	if (lock->lo_witness == NULL || witness_watch < 1 || panicstr != NULL)
		return;
	class = LOCK_CLASS(lock);
	if ((class->lc_flags & LC_SLEEPLOCK) != 0)
		instance = find_instance(curthread->td_sleeplocks, lock);
	else if ((class->lc_flags & LC_SPINLOCK) != 0)
		instance = find_instance(PCPU_GET(spinlocks), lock);
	else {
		kassert_panic("Lock (%s) %s is not sleep or spin!",
		    class->lc_name, lock->lo_name);
		return;
	}
	switch (flags) {
	case LA_UNLOCKED:
		if (instance != NULL)
			kassert_panic("Lock (%s) %s locked @ %s:%d.",
			    class->lc_name, lock->lo_name,
			    fixup_filename(file), line);
		break;
	case LA_LOCKED:
	case LA_LOCKED | LA_RECURSED:
	case LA_LOCKED | LA_NOTRECURSED:
	case LA_SLOCKED:
	case LA_SLOCKED | LA_RECURSED:
	case LA_SLOCKED | LA_NOTRECURSED:
	case LA_XLOCKED:
	case LA_XLOCKED | LA_RECURSED:
	case LA_XLOCKED | LA_NOTRECURSED:
		if (instance == NULL) {
			kassert_panic("Lock (%s) %s not locked @ %s:%d.",
			    class->lc_name, lock->lo_name,
			    fixup_filename(file), line);
			break;
		}
		if ((flags & LA_XLOCKED) != 0 &&
		    (instance->li_flags & LI_EXCLUSIVE) == 0)
			kassert_panic(
			    "Lock (%s) %s not exclusively locked @ %s:%d.",
			    class->lc_name, lock->lo_name,
			    fixup_filename(file), line);
		if ((flags & LA_SLOCKED) != 0 &&
		    (instance->li_flags & LI_EXCLUSIVE) != 0)
			kassert_panic(
			    "Lock (%s) %s exclusively locked @ %s:%d.",
			    class->lc_name, lock->lo_name,
			    fixup_filename(file), line);
		if ((flags & LA_RECURSED) != 0 &&
		    (instance->li_flags & LI_RECURSEMASK) == 0)
			kassert_panic("Lock (%s) %s not recursed @ %s:%d.",
			    class->lc_name, lock->lo_name,
			    fixup_filename(file), line);
		if ((flags & LA_NOTRECURSED) != 0 &&
		    (instance->li_flags & LI_RECURSEMASK) != 0)
			kassert_panic("Lock (%s) %s recursed @ %s:%d.",
			    class->lc_name, lock->lo_name,
			    fixup_filename(file), line);
		break;
	default:
		kassert_panic("Invalid lock assertion at %s:%d.",
		    fixup_filename(file), line);

	}
#endif	/* INVARIANT_SUPPORT */
}