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
struct lockf_entry {struct lock_owner* lf_owner; } ;
struct lock_owner {size_t lo_hash; int /*<<< orphan*/  lo_refs; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_LOCKF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 TYPE_1__* lf_lock_owners ; 
 int lockf_debug ; 
 struct lockf_entry* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,struct lockf_entry*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct lockf_entry *
lf_alloc_lock(struct lock_owner *lo)
{
	struct lockf_entry *lf;

	lf = malloc(sizeof(struct lockf_entry), M_LOCKF, M_WAITOK|M_ZERO);

#ifdef LOCKF_DEBUG
	if (lockf_debug & 4)
		printf("Allocated lock %p\n", lf);
#endif
	if (lo) {
		sx_xlock(&lf_lock_owners[lo->lo_hash].lock);
		lo->lo_refs++;
		sx_xunlock(&lf_lock_owners[lo->lo_hash].lock);
		lf->lf_owner = lo;
	}

	return (lf);
}