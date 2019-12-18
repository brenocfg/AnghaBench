#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int sa_family; } ;
struct sctp_tcb {struct sctp_inpcb* sctp_ep; } ;
struct TYPE_3__ {int inp_vflag; } ;
struct TYPE_4__ {TYPE_1__ inp; } ;
struct sctp_inpcb {int sctp_flags; TYPE_2__ ip_inp; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int INP_IPV4 ; 
 int INP_IPV6 ; 
 int SCTP_PCB_FLAGS_BOUNDALL ; 

int
sctp_destination_is_reachable(struct sctp_tcb *stcb, struct sockaddr *destaddr)
{
	struct sctp_inpcb *inp;
	int answer;

	/*
	 * No locks here, the TCB, in all cases is already locked and an
	 * assoc is up. There is either a INP lock by the caller applied (in
	 * asconf case when deleting an address) or NOT in the HB case,
	 * however if HB then the INP increment is up and the INP will not
	 * be removed (on top of the fact that we have a TCB lock). So we
	 * only want to read the sctp_flags, which is either bound-all or
	 * not.. no protection needed since once an assoc is up you can't be
	 * changing your binding.
	 */
	inp = stcb->sctp_ep;
	if (inp->sctp_flags & SCTP_PCB_FLAGS_BOUNDALL) {
		/* if bound all, destination is not restricted */
		/*
		 * RRS: Question during lock work: Is this correct? If you
		 * are bound-all you still might need to obey the V4--V6
		 * flags??? IMO this bound-all stuff needs to be removed!
		 */
		return (1);
	}
	/* NOTE: all "scope" checks are done when local addresses are added */
	switch (destaddr->sa_family) {
#ifdef INET6
	case AF_INET6:
		answer = inp->ip_inp.inp.inp_vflag & INP_IPV6;
		break;
#endif
#ifdef INET
	case AF_INET:
		answer = inp->ip_inp.inp.inp_vflag & INP_IPV4;
		break;
#endif
	default:
		/* invalid family, so it's unreachable */
		answer = 0;
		break;
	}
	return (answer);
}