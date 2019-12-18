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
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct linux_file {int f_count; int /*<<< orphan*/  f_kqlock; TYPE_1__ f_selinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  knlist_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct linux_file* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linux_kq_lock ; 
 int /*<<< orphan*/  linux_kq_lock_owned ; 
 int /*<<< orphan*/  linux_kq_lock_unowned ; 
 int /*<<< orphan*/  linux_kq_unlock ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct linux_file *
linux_file_alloc(void)
{
	struct linux_file *filp;

	filp = kzalloc(sizeof(*filp), GFP_KERNEL);

	/* set initial refcount */
	filp->f_count = 1;

	/* setup fields needed by kqueue support */
	spin_lock_init(&filp->f_kqlock);
	knlist_init(&filp->f_selinfo.si_note, &filp->f_kqlock,
	    linux_kq_lock, linux_kq_unlock,
	    linux_kq_lock_owned, linux_kq_lock_unowned);

	return (filp);
}