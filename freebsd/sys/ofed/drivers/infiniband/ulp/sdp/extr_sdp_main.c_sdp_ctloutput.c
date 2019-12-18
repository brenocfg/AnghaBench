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
struct sockopt {scalar_t__ sopt_level; int sopt_name; int sopt_dir; } ;
struct socket {int so_options; } ;
struct sdp_sock {int flags; } ;

/* Variables and functions */
 int ECONNRESET ; 
 int ENOPROTOOPT ; 
 scalar_t__ IPPROTO_TCP ; 
 int SDP_DROPPED ; 
 int SDP_NODELAY ; 
 int SDP_TIMEWAIT ; 
 int /*<<< orphan*/  SDP_WLOCK (struct sdp_sock*) ; 
 int /*<<< orphan*/  SDP_WLOCK_RECHECK (struct sdp_sock*) ; 
 int /*<<< orphan*/  SDP_WUNLOCK (struct sdp_sock*) ; 
 scalar_t__ SOL_SOCKET ; 
#define  SOPT_GET 130 
#define  SOPT_SET 129 
 int SO_KEEPALIVE ; 
#define  TCP_NODELAY 128 
 int /*<<< orphan*/  sdp_do_posts (struct sdp_sock*) ; 
 struct sdp_sock* sdp_sk (struct socket*) ; 
 int /*<<< orphan*/  sdp_start_keepalive_timer (struct socket*) ; 
 int /*<<< orphan*/  sdp_stop_keepalive_timer (struct socket*) ; 
 int sooptcopyin (struct sockopt*,int*,int,int) ; 
 int sooptcopyout (struct sockopt*,int*,int) ; 

__attribute__((used)) static int
sdp_ctloutput(struct socket *so, struct sockopt *sopt)
{
	int	error, opt, optval;
	struct sdp_sock *ssk;

	error = 0;
	ssk = sdp_sk(so);
	if (sopt->sopt_level == SOL_SOCKET && sopt->sopt_name == SO_KEEPALIVE) {
		SDP_WLOCK(ssk);
		if (so->so_options & SO_KEEPALIVE)
			sdp_start_keepalive_timer(so);
		else
			sdp_stop_keepalive_timer(so);
		SDP_WUNLOCK(ssk);
	}
	if (sopt->sopt_level != IPPROTO_TCP)
		return (error);

	SDP_WLOCK(ssk);
	if (ssk->flags & (SDP_TIMEWAIT | SDP_DROPPED)) {
		SDP_WUNLOCK(ssk);
		return (ECONNRESET);
	}

	switch (sopt->sopt_dir) {
	case SOPT_SET:
		switch (sopt->sopt_name) {
		case TCP_NODELAY:
			SDP_WUNLOCK(ssk);
			error = sooptcopyin(sopt, &optval, sizeof optval,
			    sizeof optval);
			if (error)
				return (error);

			SDP_WLOCK_RECHECK(ssk);
			opt = SDP_NODELAY;
			if (optval)
				ssk->flags |= opt;
			else
				ssk->flags &= ~opt;
			sdp_do_posts(ssk);
			SDP_WUNLOCK(ssk);
			break;

		default:
			SDP_WUNLOCK(ssk);
			error = ENOPROTOOPT;
			break;
		}
		break;

	case SOPT_GET:
		switch (sopt->sopt_name) {
		case TCP_NODELAY:
			optval = ssk->flags & SDP_NODELAY;
			SDP_WUNLOCK(ssk);
			error = sooptcopyout(sopt, &optval, sizeof optval);
			break;
		default:
			SDP_WUNLOCK(ssk);
			error = ENOPROTOOPT;
			break;
		}
		break;
	}
	return (error);
}