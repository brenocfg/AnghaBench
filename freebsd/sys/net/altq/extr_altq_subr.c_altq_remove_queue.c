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
#define  ALTQT_CBQ 131 
#define  ALTQT_FAIRQ 130 
#define  ALTQT_HFSC 129 
#define  ALTQT_PRIQ 128 
 int ENXIO ; 
 int cbq_remove_queue (struct pf_altq*) ; 
 int fairq_remove_queue (struct pf_altq*) ; 
 int hfsc_remove_queue (struct pf_altq*) ; 
 int priq_remove_queue (struct pf_altq*) ; 

int
altq_remove_queue(struct pf_altq *a)
{
	int error = 0;

	switch (a->scheduler) {
#ifdef ALTQ_CBQ
	case ALTQT_CBQ:
		error = cbq_remove_queue(a);
		break;
#endif
#ifdef ALTQ_PRIQ
	case ALTQT_PRIQ:
		error = priq_remove_queue(a);
		break;
#endif
#ifdef ALTQ_HFSC
	case ALTQT_HFSC:
		error = hfsc_remove_queue(a);
		break;
#endif
#ifdef ALTQ_FAIRQ
        case ALTQT_FAIRQ:
                error = fairq_remove_queue(a);
                break;
#endif
	default:
		error = ENXIO;
	}

	return (error);
}