#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockbuf {int sb_flags; int (* sb_upcall ) (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  sb_upcallarg; TYPE_1__* sb_sel; int /*<<< orphan*/  sb_acc; } ;
struct socket {int so_state; int /*<<< orphan*/ * so_sigio; struct sockbuf so_rcv; } ;
struct TYPE_3__ {int /*<<< orphan*/  si_note; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KNOTE_LOCKED (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PSOCK ; 
 int SB_AIO ; 
 int SB_SEL ; 
 int SB_WAIT ; 
 int /*<<< orphan*/  SEL_WAITING (TYPE_1__*) ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  SOCKBUF_LOCK_ASSERT (struct sockbuf*) ; 
 int /*<<< orphan*/  SOCKBUF_MTX (struct sockbuf*) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (struct sockbuf*) ; 
 int /*<<< orphan*/  SO_RCV ; 
 int SS_ASYNC ; 
 int SU_ISCONNECTED ; 
 int SU_OK ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgsigio (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selwakeuppri (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soisconnected (struct socket*) ; 
 int /*<<< orphan*/  soupcall_clear (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sowakeup_aio (struct socket*,struct sockbuf*) ; 
 int stub1 (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

void
sowakeup(struct socket *so, struct sockbuf *sb)
{
	int ret;

	SOCKBUF_LOCK_ASSERT(sb);

	selwakeuppri(sb->sb_sel, PSOCK);
	if (!SEL_WAITING(sb->sb_sel))
		sb->sb_flags &= ~SB_SEL;
	if (sb->sb_flags & SB_WAIT) {
		sb->sb_flags &= ~SB_WAIT;
		wakeup(&sb->sb_acc);
	}
	KNOTE_LOCKED(&sb->sb_sel->si_note, 0);
	if (sb->sb_upcall != NULL) {
		ret = sb->sb_upcall(so, sb->sb_upcallarg, M_NOWAIT);
		if (ret == SU_ISCONNECTED) {
			KASSERT(sb == &so->so_rcv,
			    ("SO_SND upcall returned SU_ISCONNECTED"));
			soupcall_clear(so, SO_RCV);
		}
	} else
		ret = SU_OK;
	if (sb->sb_flags & SB_AIO)
		sowakeup_aio(so, sb);
	SOCKBUF_UNLOCK(sb);
	if (ret == SU_ISCONNECTED)
		soisconnected(so);
	if ((so->so_state & SS_ASYNC) && so->so_sigio != NULL)
		pgsigio(&so->so_sigio, SIGIO, 0);
	mtx_assert(SOCKBUF_MTX(sb), MA_NOTOWNED);
}