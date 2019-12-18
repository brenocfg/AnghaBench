#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sb_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  si_note; } ;
struct socket {TYPE_3__ so_snd; TYPE_2__ so_wrsel; } ;
struct knote {TYPE_1__* kn_fp; } ;
struct TYPE_4__ {struct socket* f_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SB_KNOTE ; 
 int /*<<< orphan*/  SOLISTENING (struct socket*) ; 
 scalar_t__ knlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  knlist_remove (int /*<<< orphan*/ *,struct knote*,int) ; 
 int /*<<< orphan*/  so_wrknl_lock (struct socket*) ; 
 int /*<<< orphan*/  so_wrknl_unlock (struct socket*) ; 

__attribute__((used)) static void
filt_sowdetach(struct knote *kn)
{
	struct socket *so = kn->kn_fp->f_data;

	so_wrknl_lock(so);
	knlist_remove(&so->so_wrsel.si_note, kn, 1);
	if (!SOLISTENING(so) && knlist_empty(&so->so_wrsel.si_note))
		so->so_snd.sb_flags &= ~SB_KNOTE;
	so_wrknl_unlock(so);
}