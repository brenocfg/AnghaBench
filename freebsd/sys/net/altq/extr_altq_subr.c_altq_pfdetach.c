#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pf_altq {scalar_t__ altq_disc; int /*<<< orphan*/  ifname; } ;
struct TYPE_4__ {scalar_t__ altq_disc; } ;
struct ifnet {TYPE_1__ if_snd; } ;

/* Variables and functions */
 scalar_t__ ALTQ_IS_ENABLED (TYPE_1__*) ; 
 int EINVAL ; 
 int altq_detach (TYPE_1__*) ; 
 int altq_disable (TYPE_1__*) ; 
 struct ifnet* ifunit (int /*<<< orphan*/ ) ; 
 int splnet () ; 
 int /*<<< orphan*/  splx (int) ; 

int
altq_pfdetach(struct pf_altq *a)
{
	struct ifnet *ifp;
	int s, error = 0;

	if ((ifp = ifunit(a->ifname)) == NULL)
		return (EINVAL);

	/* if this discipline is no longer referenced, just return */
	/* read unlocked from if_snd */
	if (a->altq_disc == NULL || a->altq_disc != ifp->if_snd.altq_disc)
		return (0);

	s = splnet();
	/* read unlocked from if_snd, _disable and _detach take care */
	if (ALTQ_IS_ENABLED(&ifp->if_snd))
		error = altq_disable(&ifp->if_snd);
	if (error == 0)
		error = altq_detach(&ifp->if_snd);
	splx(s);

	return (error);
}