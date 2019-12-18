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
struct linux_file {int /*<<< orphan*/  f_kqlock; TYPE_1__ f_selinfo; } ;
struct knote {struct linux_file* kn_hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  knlist_remove (int /*<<< orphan*/ *,struct knote*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
linux_file_kqfilter_detach(struct knote *kn)
{
	struct linux_file *filp = kn->kn_hook;

	spin_lock(&filp->f_kqlock);
	knlist_remove(&filp->f_selinfo.si_note, kn, 1);
	spin_unlock(&filp->f_kqlock);
}