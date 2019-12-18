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
struct ifnet {int /*<<< orphan*/  if_xname; } ;
struct ifaltq {scalar_t__ ifq_maxlen; struct ifnet* altq_ifp; int /*<<< orphan*/ * altq_tbr; int /*<<< orphan*/  altq_flags; int /*<<< orphan*/ * altq_disc; scalar_t__ altq_type; int /*<<< orphan*/  ifq_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALTQF_CANTCHANGE ; 
 int /*<<< orphan*/  MTX_DEF ; 
 scalar_t__ ifqmaxlen ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
ifq_init(struct ifaltq *ifq, struct ifnet *ifp)
{
	
	mtx_init(&ifq->ifq_mtx, ifp->if_xname, "if send queue", MTX_DEF);

	if (ifq->ifq_maxlen == 0) 
		ifq->ifq_maxlen = ifqmaxlen;

	ifq->altq_type = 0;
	ifq->altq_disc = NULL;
	ifq->altq_flags &= ALTQF_CANTCHANGE;
	ifq->altq_tbr  = NULL;
	ifq->altq_ifp  = ifp;
}