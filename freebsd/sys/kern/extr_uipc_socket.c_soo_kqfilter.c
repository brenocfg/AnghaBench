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
struct sockbuf {int /*<<< orphan*/  sb_flags; } ;
struct knlist {int dummy; } ;
struct TYPE_6__ {struct knlist si_note; } ;
struct TYPE_5__ {struct knlist si_note; } ;
struct socket {struct sockbuf so_snd; TYPE_3__ so_wrsel; struct sockbuf so_rcv; TYPE_2__ so_rdsel; } ;
struct knote {int kn_filter; int /*<<< orphan*/ * kn_fop; TYPE_1__* kn_fp; } ;
struct file {int dummy; } ;
struct TYPE_4__ {struct socket* f_data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  EVFILT_EMPTY 130 
#define  EVFILT_READ 129 
#define  EVFILT_WRITE 128 
 int /*<<< orphan*/  SB_KNOTE ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (struct sockbuf*) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (struct sockbuf*) ; 
 int /*<<< orphan*/  SOCK_LOCK (struct socket*) ; 
 int /*<<< orphan*/  SOCK_UNLOCK (struct socket*) ; 
 scalar_t__ SOLISTENING (struct socket*) ; 
 int /*<<< orphan*/  knlist_add (struct knlist*,struct knote*,int) ; 
 int /*<<< orphan*/  soempty_filtops ; 
 int /*<<< orphan*/  soread_filtops ; 
 int /*<<< orphan*/  sowrite_filtops ; 

int
soo_kqfilter(struct file *fp, struct knote *kn)
{
	struct socket *so = kn->kn_fp->f_data;
	struct sockbuf *sb;
	struct knlist *knl;

	switch (kn->kn_filter) {
	case EVFILT_READ:
		kn->kn_fop = &soread_filtops;
		knl = &so->so_rdsel.si_note;
		sb = &so->so_rcv;
		break;
	case EVFILT_WRITE:
		kn->kn_fop = &sowrite_filtops;
		knl = &so->so_wrsel.si_note;
		sb = &so->so_snd;
		break;
	case EVFILT_EMPTY:
		kn->kn_fop = &soempty_filtops;
		knl = &so->so_wrsel.si_note;
		sb = &so->so_snd;
		break;
	default:
		return (EINVAL);
	}

	SOCK_LOCK(so);
	if (SOLISTENING(so)) {
		knlist_add(knl, kn, 1);
	} else {
		SOCKBUF_LOCK(sb);
		knlist_add(knl, kn, 1);
		sb->sb_flags |= SB_KNOTE;
		SOCKBUF_UNLOCK(sb);
	}
	SOCK_UNLOCK(so);
	return (0);
}