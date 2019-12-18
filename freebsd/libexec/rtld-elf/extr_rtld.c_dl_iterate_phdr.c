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
struct dl_phdr_info {int dummy; } ;
typedef  int /*<<< orphan*/  phdr_info ;
typedef  int (* __dl_iterate_hdr_callback ) (struct dl_phdr_info*,int,void*) ;
typedef  int /*<<< orphan*/  RtldLockState ;
typedef  int /*<<< orphan*/  Obj_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * globallist_curr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * globallist_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hold_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_marker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_release (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  obj_list ; 
 int /*<<< orphan*/  obj_rtld ; 
 int /*<<< orphan*/  rtld_bind_lock ; 
 int /*<<< orphan*/  rtld_fill_dl_phdr_info (int /*<<< orphan*/ *,struct dl_phdr_info*) ; 
 int /*<<< orphan*/  rtld_phdr_lock ; 
 int /*<<< orphan*/  unhold_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlock_acquire (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
dl_iterate_phdr(__dl_iterate_hdr_callback callback, void *param)
{
	struct dl_phdr_info phdr_info;
	Obj_Entry *obj, marker;
	RtldLockState bind_lockstate, phdr_lockstate;
	int error;

	init_marker(&marker);
	error = 0;

	wlock_acquire(rtld_phdr_lock, &phdr_lockstate);
	wlock_acquire(rtld_bind_lock, &bind_lockstate);
	for (obj = globallist_curr(TAILQ_FIRST(&obj_list)); obj != NULL;) {
		TAILQ_INSERT_AFTER(&obj_list, obj, &marker, next);
		rtld_fill_dl_phdr_info(obj, &phdr_info);
		hold_object(obj);
		lock_release(rtld_bind_lock, &bind_lockstate);

		error = callback(&phdr_info, sizeof phdr_info, param);

		wlock_acquire(rtld_bind_lock, &bind_lockstate);
		unhold_object(obj);
		obj = globallist_next(&marker);
		TAILQ_REMOVE(&obj_list, &marker, next);
		if (error != 0) {
			lock_release(rtld_bind_lock, &bind_lockstate);
			lock_release(rtld_phdr_lock, &phdr_lockstate);
			return (error);
		}
	}

	if (error == 0) {
		rtld_fill_dl_phdr_info(&obj_rtld, &phdr_info);
		lock_release(rtld_bind_lock, &bind_lockstate);
		error = callback(&phdr_info, sizeof(phdr_info), param);
	}
	lock_release(rtld_phdr_lock, &phdr_lockstate);
	return (error);
}