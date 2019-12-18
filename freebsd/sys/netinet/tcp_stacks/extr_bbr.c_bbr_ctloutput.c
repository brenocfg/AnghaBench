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
struct tcpcb {scalar_t__ t_fb_ptr; } ;
struct tcp_bbr {int dummy; } ;
struct sockopt {scalar_t__ sopt_dir; } ;
struct socket {int dummy; } ;
struct inpcb {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 scalar_t__ SOPT_GET ; 
 scalar_t__ SOPT_SET ; 
 int bbr_get_sockopt (struct socket*,struct sockopt*,struct inpcb*,struct tcpcb*,struct tcp_bbr*) ; 
 int bbr_set_sockopt (struct socket*,struct sockopt*,struct inpcb*,struct tcpcb*,struct tcp_bbr*) ; 

__attribute__((used)) static int
bbr_ctloutput(struct socket *so, struct sockopt *sopt, struct inpcb *inp, struct tcpcb *tp)
{
	int32_t error = EINVAL;
	struct tcp_bbr *bbr;

	bbr = (struct tcp_bbr *)tp->t_fb_ptr;
	if (bbr == NULL) {
		/* Huh? */
		goto out;
	}
	if (sopt->sopt_dir == SOPT_SET) {
		return (bbr_set_sockopt(so, sopt, inp, tp, bbr));
	} else if (sopt->sopt_dir == SOPT_GET) {
		return (bbr_get_sockopt(so, sopt, inp, tp, bbr));
	}
out:
	INP_WUNLOCK(inp);
	return (error);
}