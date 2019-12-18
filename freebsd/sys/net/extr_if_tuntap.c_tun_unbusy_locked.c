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
struct tuntap_softc {scalar_t__ tun_busy; int /*<<< orphan*/  tun_cv; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  TUN_LOCK_ASSERT (struct tuntap_softc*) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tun_unbusy_locked(struct tuntap_softc *tp)
{

	TUN_LOCK_ASSERT(tp);
	KASSERT(tp->tun_busy != 0, ("tun_unbusy: called for non-busy tunnel"));

	--tp->tun_busy;
	/* Wake up anything that may be waiting on our busy tunnel. */
	if (tp->tun_busy == 0)
		cv_broadcast(&tp->tun_cv);
}