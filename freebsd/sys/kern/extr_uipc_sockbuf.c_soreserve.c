#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct thread {int dummy; } ;
struct TYPE_5__ {int sb_lowat; scalar_t__ sb_hiwat; } ;
struct socket {TYPE_1__ so_snd; TYPE_1__ so_rcv; } ;

/* Variables and functions */
 int ENOBUFS ; 
 scalar_t__ MCLBYTES ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (TYPE_1__*) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  sbrelease_locked (TYPE_1__*,struct socket*) ; 
 scalar_t__ sbreserve_locked (TYPE_1__*,int /*<<< orphan*/ ,struct socket*,struct thread*) ; 

int
soreserve(struct socket *so, u_long sndcc, u_long rcvcc)
{
	struct thread *td = curthread;

	SOCKBUF_LOCK(&so->so_snd);
	SOCKBUF_LOCK(&so->so_rcv);
	if (sbreserve_locked(&so->so_snd, sndcc, so, td) == 0)
		goto bad;
	if (sbreserve_locked(&so->so_rcv, rcvcc, so, td) == 0)
		goto bad2;
	if (so->so_rcv.sb_lowat == 0)
		so->so_rcv.sb_lowat = 1;
	if (so->so_snd.sb_lowat == 0)
		so->so_snd.sb_lowat = MCLBYTES;
	if (so->so_snd.sb_lowat > so->so_snd.sb_hiwat)
		so->so_snd.sb_lowat = so->so_snd.sb_hiwat;
	SOCKBUF_UNLOCK(&so->so_rcv);
	SOCKBUF_UNLOCK(&so->so_snd);
	return (0);
bad2:
	sbrelease_locked(&so->so_snd, so);
bad:
	SOCKBUF_UNLOCK(&so->so_rcv);
	SOCKBUF_UNLOCK(&so->so_snd);
	return (ENOBUFS);
}