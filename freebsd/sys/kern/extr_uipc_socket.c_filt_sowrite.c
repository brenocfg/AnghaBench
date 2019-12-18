#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int sb_state; scalar_t__ sb_lowat; } ;
struct socket {int so_state; TYPE_3__ so_snd; TYPE_2__* so_proto; scalar_t__ so_error; } ;
struct knote {scalar_t__ kn_data; int kn_sfflags; scalar_t__ kn_sdata; scalar_t__ kn_fflags; int /*<<< orphan*/  kn_flags; TYPE_1__* kn_fp; } ;
struct TYPE_6__ {int pr_flags; } ;
struct TYPE_5__ {struct socket* f_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_EOF ; 
 int /*<<< orphan*/  HHOOK_FILT_SOWRITE ; 
 int NOTE_LOWAT ; 
 int PR_CONNREQUIRED ; 
 int SBS_CANTSENDMORE ; 
 int /*<<< orphan*/  SOCKBUF_LOCK_ASSERT (TYPE_3__*) ; 
 scalar_t__ SOLISTENING (struct socket*) ; 
 int SS_ISCONNECTED ; 
 int /*<<< orphan*/  hhook_run_socket (struct socket*,struct knote*,int /*<<< orphan*/ ) ; 
 scalar_t__ sbspace (TYPE_3__*) ; 

__attribute__((used)) static int
filt_sowrite(struct knote *kn, long hint)
{
	struct socket *so;

	so = kn->kn_fp->f_data;

	if (SOLISTENING(so))
		return (0);

	SOCKBUF_LOCK_ASSERT(&so->so_snd);
	kn->kn_data = sbspace(&so->so_snd);

	hhook_run_socket(so, kn, HHOOK_FILT_SOWRITE);

	if (so->so_snd.sb_state & SBS_CANTSENDMORE) {
		kn->kn_flags |= EV_EOF;
		kn->kn_fflags = so->so_error;
		return (1);
	} else if (so->so_error)	/* temporary udp error */
		return (1);
	else if (((so->so_state & SS_ISCONNECTED) == 0) &&
	    (so->so_proto->pr_flags & PR_CONNREQUIRED))
		return (0);
	else if (kn->kn_sfflags & NOTE_LOWAT)
		return (kn->kn_data >= kn->kn_sdata);
	else
		return (kn->kn_data >= so->so_snd.sb_lowat);
}