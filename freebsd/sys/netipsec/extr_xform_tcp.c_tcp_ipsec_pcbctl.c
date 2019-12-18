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
struct tcpcb {int t_flags; } ;
struct sockopt {scalar_t__ sopt_name; scalar_t__ sopt_dir; } ;
struct inpcb {int inp_flags; } ;
typedef  int /*<<< orphan*/  optval ;

/* Variables and functions */
 int ECONNRESET ; 
 int ENOPROTOOPT ; 
 int INP_DROPPED ; 
 int /*<<< orphan*/  INP_RLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  INP_RUNLOCK (struct inpcb*) ; 
 int INP_TIMEWAIT ; 
 int /*<<< orphan*/  INP_WLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 scalar_t__ SOPT_GET ; 
 scalar_t__ TCP_MD5SIG ; 
 int TF_SIGNATURE ; 
 struct tcpcb* intotcpcb (struct inpcb*) ; 
 int sooptcopyin (struct sockopt*,int*,int,int) ; 
 int sooptcopyout (struct sockopt*,int*,int) ; 

__attribute__((used)) static int
tcp_ipsec_pcbctl(struct inpcb *inp, struct sockopt *sopt)
{
	struct tcpcb *tp;
	int error, optval;

	if (sopt->sopt_name != TCP_MD5SIG) {
		return (ENOPROTOOPT);
	}

	if (sopt->sopt_dir == SOPT_GET) {
		INP_RLOCK(inp);
		if (inp->inp_flags & (INP_TIMEWAIT | INP_DROPPED)) {
			INP_RUNLOCK(inp);
			return (ECONNRESET);
		}
		tp = intotcpcb(inp);
		optval = (tp->t_flags & TF_SIGNATURE) ? 1 : 0;
		INP_RUNLOCK(inp);

		/* On success return with released INP_WLOCK */
		return (sooptcopyout(sopt, &optval, sizeof(optval)));
	}

	error = sooptcopyin(sopt, &optval, sizeof(optval), sizeof(optval));
	if (error != 0)
		return (error);

	/* INP_WLOCK_RECHECK */
	INP_WLOCK(inp);
	if (inp->inp_flags & (INP_TIMEWAIT | INP_DROPPED)) {
		INP_WUNLOCK(inp);
		return (ECONNRESET);
	}
	tp = intotcpcb(inp);
	if (optval > 0)
		tp->t_flags |= TF_SIGNATURE;
	else
		tp->t_flags &= ~TF_SIGNATURE;

	INP_WUNLOCK(inp);
	return (error);
}