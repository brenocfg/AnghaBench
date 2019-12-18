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
struct pf_altq {scalar_t__* qname; int scheduler; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
#define  ALTQT_CBQ 132 
#define  ALTQT_CODEL 131 
#define  ALTQT_FAIRQ 130 
#define  ALTQT_HFSC 129 
#define  ALTQT_PRIQ 128 
 int ENXIO ; 
 int altq_add_queue (struct pf_altq*) ; 
 int cbq_add_altq (struct ifnet*,struct pf_altq*) ; 
 int codel_add_altq (struct ifnet*,struct pf_altq*) ; 
 int fairq_add_altq (struct ifnet*,struct pf_altq*) ; 
 int hfsc_add_altq (struct ifnet*,struct pf_altq*) ; 
 int /*<<< orphan*/  init_machclk () ; 
 scalar_t__ machclk_freq ; 
 int /*<<< orphan*/  panic (char*) ; 
 int priq_add_altq (struct ifnet*,struct pf_altq*) ; 

int
altq_add(struct ifnet *ifp, struct pf_altq *a)
{
	int error = 0;

	if (a->qname[0] != 0)
		return (altq_add_queue(a));

	if (machclk_freq == 0)
		init_machclk();
	if (machclk_freq == 0)
		panic("altq_add: no cpu clock");

	switch (a->scheduler) {
#ifdef ALTQ_CBQ
	case ALTQT_CBQ:
		error = cbq_add_altq(ifp, a);
		break;
#endif
#ifdef ALTQ_PRIQ
	case ALTQT_PRIQ:
		error = priq_add_altq(ifp, a);
		break;
#endif
#ifdef ALTQ_HFSC
	case ALTQT_HFSC:
		error = hfsc_add_altq(ifp, a);
		break;
#endif
#ifdef ALTQ_FAIRQ
        case ALTQT_FAIRQ:
                error = fairq_add_altq(ifp, a);
                break;
#endif
#ifdef ALTQ_CODEL
	case ALTQT_CODEL:
		error = codel_add_altq(ifp, a);
		break;
#endif
	default:
		error = ENXIO;
	}

	return (error);
}