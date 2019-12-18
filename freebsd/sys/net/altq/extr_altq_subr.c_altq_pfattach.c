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
struct pf_altq {int scheduler; } ;

/* Variables and functions */
#define  ALTQT_CBQ 133 
#define  ALTQT_CODEL 132 
#define  ALTQT_FAIRQ 131 
#define  ALTQT_HFSC 130 
#define  ALTQT_NONE 129 
#define  ALTQT_PRIQ 128 
 int ENXIO ; 
 int cbq_pfattach (struct pf_altq*) ; 
 int codel_pfattach (struct pf_altq*) ; 
 int fairq_pfattach (struct pf_altq*) ; 
 int hfsc_pfattach (struct pf_altq*) ; 
 int priq_pfattach (struct pf_altq*) ; 

int
altq_pfattach(struct pf_altq *a)
{
	int error = 0;

	switch (a->scheduler) {
	case ALTQT_NONE:
		break;
#ifdef ALTQ_CBQ
	case ALTQT_CBQ:
		error = cbq_pfattach(a);
		break;
#endif
#ifdef ALTQ_PRIQ
	case ALTQT_PRIQ:
		error = priq_pfattach(a);
		break;
#endif
#ifdef ALTQ_HFSC
	case ALTQT_HFSC:
		error = hfsc_pfattach(a);
		break;
#endif
#ifdef ALTQ_FAIRQ
	case ALTQT_FAIRQ:
		error = fairq_pfattach(a);
		break;
#endif
#ifdef ALTQ_CODEL
	case ALTQT_CODEL:
		error = codel_pfattach(a);
		break;
#endif
	default:
		error = ENXIO;
	}

	return (error);
}