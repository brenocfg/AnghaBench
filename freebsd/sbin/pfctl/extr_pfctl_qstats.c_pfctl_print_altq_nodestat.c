#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ qid; int scheduler; int local_flags; } ;
struct pf_altq_node {int /*<<< orphan*/  qstats; TYPE_1__ altq; } ;

/* Variables and functions */
#define  ALTQT_CBQ 132 
#define  ALTQT_CODEL 131 
#define  ALTQT_FAIRQ 130 
#define  ALTQT_HFSC 129 
#define  ALTQT_PRIQ 128 
 int PFALTQ_FLAG_IF_REMOVED ; 
 int /*<<< orphan*/  print_cbqstats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_codelstats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_fairqstats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hfscstats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_priqstats (int /*<<< orphan*/ ) ; 

void
pfctl_print_altq_nodestat(int dev, const struct pf_altq_node *a)
{
	if (a->altq.qid == 0 && a->altq.scheduler != ALTQT_CODEL)
		return;

#ifdef __FreeBSD__
	if (a->altq.local_flags & PFALTQ_FLAG_IF_REMOVED)
		return;
#endif
	switch (a->altq.scheduler) {
	case ALTQT_CBQ:
		print_cbqstats(a->qstats);
		break;
	case ALTQT_PRIQ:
		print_priqstats(a->qstats);
		break;
	case ALTQT_HFSC:
		print_hfscstats(a->qstats);
		break;
	case ALTQT_FAIRQ:
		print_fairqstats(a->qstats);
		break;
	case ALTQT_CODEL:
		print_codelstats(a->qstats);
		break;
	}
}