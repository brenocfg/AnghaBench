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
struct knlist {void (* kl_lock ) (void*) ;void (* kl_unlock ) (void*) ;void (* kl_assert_locked ) (void*) ;void (* kl_assert_unlocked ) (void*) ;int /*<<< orphan*/  kl_list; scalar_t__ kl_autodestroy; int /*<<< orphan*/ * kl_lockarg; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  knlist_lock ; 
 void knlist_mtx_assert_locked (void*) ; 
 void knlist_mtx_assert_unlocked (void*) ; 
 void knlist_mtx_lock (void*) ; 
 void knlist_mtx_unlock (void*) ; 

void
knlist_init(struct knlist *knl, void *lock, void (*kl_lock)(void *),
    void (*kl_unlock)(void *),
    void (*kl_assert_locked)(void *), void (*kl_assert_unlocked)(void *))
{

	if (lock == NULL)
		knl->kl_lockarg = &knlist_lock;
	else
		knl->kl_lockarg = lock;

	if (kl_lock == NULL)
		knl->kl_lock = knlist_mtx_lock;
	else
		knl->kl_lock = kl_lock;
	if (kl_unlock == NULL)
		knl->kl_unlock = knlist_mtx_unlock;
	else
		knl->kl_unlock = kl_unlock;
	if (kl_assert_locked == NULL)
		knl->kl_assert_locked = knlist_mtx_assert_locked;
	else
		knl->kl_assert_locked = kl_assert_locked;
	if (kl_assert_unlocked == NULL)
		knl->kl_assert_unlocked = knlist_mtx_assert_unlocked;
	else
		knl->kl_assert_unlocked = kl_assert_unlocked;

	knl->kl_autodestroy = 0;
	SLIST_INIT(&knl->kl_list);
}