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
typedef  scalar_t__ uint32_t ;
struct tcpcb {int snd_wnd; scalar_t__ snd_nxt; scalar_t__ snd_una; } ;
struct TYPE_3__ {int sb_flags; int sb_lowat; int sb_hiwat; } ;
struct socket {TYPE_1__ so_snd; } ;

/* Variables and functions */
 int SB_AUTOSIZE ; 
 scalar_t__ V_tcp_autosndbuf_inc ; 
 scalar_t__ V_tcp_autosndbuf_max ; 
 scalar_t__ V_tcp_do_autosndbuf ; 
 scalar_t__ V_tcp_sendbuf_auto_lowat ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sbreserve_locked (TYPE_1__*,int /*<<< orphan*/ ,struct socket*,int /*<<< orphan*/ ) ; 
 scalar_t__ sbused (TYPE_1__*) ; 

void
tcp_sndbuf_autoscale(struct tcpcb *tp, struct socket *so, uint32_t sendwin)
{

	/*
	 * Automatic sizing of send socket buffer.  Often the send buffer
	 * size is not optimally adjusted to the actual network conditions
	 * at hand (delay bandwidth product).  Setting the buffer size too
	 * small limits throughput on links with high bandwidth and high
	 * delay (eg. trans-continental/oceanic links).  Setting the
	 * buffer size too big consumes too much real kernel memory,
	 * especially with many connections on busy servers.
	 *
	 * The criteria to step up the send buffer one notch are:
	 *  1. receive window of remote host is larger than send buffer
	 *     (with a fudge factor of 5/4th);
	 *  2. send buffer is filled to 7/8th with data (so we actually
	 *     have data to make use of it);
	 *  3. send buffer fill has not hit maximal automatic size;
	 *  4. our send window (slow start and cogestion controlled) is
	 *     larger than sent but unacknowledged data in send buffer.
	 *
	 * The remote host receive window scaling factor may limit the
	 * growing of the send buffer before it reaches its allowed
	 * maximum.
	 *
	 * It scales directly with slow start or congestion window
	 * and does at most one step per received ACK.  This fast
	 * scaling has the drawback of growing the send buffer beyond
	 * what is strictly necessary to make full use of a given
	 * delay*bandwidth product.  However testing has shown this not
	 * to be much of an problem.  At worst we are trading wasting
	 * of available bandwidth (the non-use of it) for wasting some
	 * socket buffer memory.
	 *
	 * TODO: Shrink send buffer during idle periods together
	 * with congestion window.  Requires another timer.  Has to
	 * wait for upcoming tcp timer rewrite.
	 *
	 * XXXGL: should there be used sbused() or sbavail()?
	 */
	if (V_tcp_do_autosndbuf && so->so_snd.sb_flags & SB_AUTOSIZE) {
		int lowat;

		lowat = V_tcp_sendbuf_auto_lowat ? so->so_snd.sb_lowat : 0;
		if ((tp->snd_wnd / 4 * 5) >= so->so_snd.sb_hiwat - lowat &&
		    sbused(&so->so_snd) >=
		    (so->so_snd.sb_hiwat / 8 * 7) - lowat &&
		    sbused(&so->so_snd) < V_tcp_autosndbuf_max &&
		    sendwin >= (sbused(&so->so_snd) -
		    (tp->snd_nxt - tp->snd_una))) {
			if (!sbreserve_locked(&so->so_snd,
			    min(so->so_snd.sb_hiwat + V_tcp_autosndbuf_inc,
			     V_tcp_autosndbuf_max), so, curthread))
				so->so_snd.sb_flags &= ~SB_AUTOSIZE;
		}
	}
}