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
struct lock_object {int lo_flags; char const* lo_name; } ;
struct lock_class {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LOCK_CLASS_MAX ; 
 int /*<<< orphan*/  LOCK_LOG_INIT (struct lock_object*,int /*<<< orphan*/ ) ; 
 int LO_CLASSSHIFT ; 
 int LO_INITIALIZED ; 
 int LO_NEW ; 
 int /*<<< orphan*/  WITNESS_INIT (struct lock_object*,char const*) ; 
 struct lock_class** lock_classes ; 
 int /*<<< orphan*/  lock_initialized (struct lock_object*) ; 

void
lock_init(struct lock_object *lock, struct lock_class *class, const char *name,
    const char *type, int flags)
{
	int i;

	/* Check for double-init and zero object. */
	KASSERT(flags & LO_NEW || !lock_initialized(lock),
	    ("lock \"%s\" %p already initialized", name, lock));

	/* Look up lock class to find its index. */
	for (i = 0; i < LOCK_CLASS_MAX; i++)
		if (lock_classes[i] == class) {
			lock->lo_flags = i << LO_CLASSSHIFT;
			break;
		}
	KASSERT(i < LOCK_CLASS_MAX, ("unknown lock class %p", class));

	/* Initialize the lock object. */
	lock->lo_name = name;
	lock->lo_flags |= flags | LO_INITIALIZED;
	LOCK_LOG_INIT(lock, 0);
	WITNESS_INIT(lock, (type != NULL) ? type : name);
}