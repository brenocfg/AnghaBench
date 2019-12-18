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
typedef  int u_int ;
struct cf_rendezvous {int maxrec; } ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_3__ {scalar_t__ xp_p1; } ;
typedef  TYPE_1__ SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  SVCGET_CONNMAXREC 129 
#define  SVCSET_CONNMAXREC 128 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static bool_t
svc_vc_rendezvous_control(SVCXPRT *xprt, const u_int rq, void *in)
{
	struct cf_rendezvous *cfp;

	cfp = (struct cf_rendezvous *)xprt->xp_p1;
	if (cfp == NULL)
		return (FALSE);
	switch (rq) {
		case SVCGET_CONNMAXREC:
			*(int *)in = cfp->maxrec;
			break;
		case SVCSET_CONNMAXREC:
			cfp->maxrec = *(int *)in;
			break;
		default:
			return (FALSE);
	}
	return (TRUE);
}