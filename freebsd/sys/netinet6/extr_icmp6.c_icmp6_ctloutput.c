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
struct sockopt {int sopt_level; int sopt_dir; int sopt_name; int sopt_valsize; } ;
struct socket {int dummy; } ;
struct inpcb {struct icmp6_filter* in6p_icmp6filt; } ;
struct icmp6_filter {int dummy; } ;
typedef  int /*<<< orphan*/  ic6f ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOPROTOOPT ; 
#define  ICMP6_FILTER 130 
 int /*<<< orphan*/  INP_RLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  INP_RUNLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 int IPPROTO_ICMPV6 ; 
#define  PRCO_GETOPT 129 
#define  PRCO_SETOPT 128 
 int sooptcopyin (struct sockopt*,struct icmp6_filter*,int,int) ; 
 int sooptcopyout (struct sockopt*,struct icmp6_filter*,int) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

int
icmp6_ctloutput(struct socket *so, struct sockopt *sopt)
{
	int error = 0;
	int optlen;
	struct inpcb *inp = sotoinpcb(so);
	int level, op, optname;

	if (sopt) {
		level = sopt->sopt_level;
		op = sopt->sopt_dir;
		optname = sopt->sopt_name;
		optlen = sopt->sopt_valsize;
	} else
		level = op = optname = optlen = 0;

	if (level != IPPROTO_ICMPV6) {
		return EINVAL;
	}

	switch (op) {
	case PRCO_SETOPT:
		switch (optname) {
		case ICMP6_FILTER:
		    {
			struct icmp6_filter ic6f;

			if (optlen != sizeof(ic6f)) {
				error = EMSGSIZE;
				break;
			}
			error = sooptcopyin(sopt, &ic6f, optlen, optlen);
			if (error == 0) {
				INP_WLOCK(inp);
				*inp->in6p_icmp6filt = ic6f;
				INP_WUNLOCK(inp);
			}
			break;
		    }

		default:
			error = ENOPROTOOPT;
			break;
		}
		break;

	case PRCO_GETOPT:
		switch (optname) {
		case ICMP6_FILTER:
		    {
			struct icmp6_filter ic6f;

			INP_RLOCK(inp);
			ic6f = *inp->in6p_icmp6filt;
			INP_RUNLOCK(inp);
			error = sooptcopyout(sopt, &ic6f, sizeof(ic6f));
			break;
		    }

		default:
			error = ENOPROTOOPT;
			break;
		}
		break;
	}

	return (error);
}