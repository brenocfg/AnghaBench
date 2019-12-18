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
struct tuntap_softc {int tun_flags; int /*<<< orphan*/  tun_busy; } ;

/* Variables and functions */
 int EBUSY ; 
 int TUN_DYING ; 
 int /*<<< orphan*/  TUN_LOCK_ASSERT (struct tuntap_softc*) ; 

__attribute__((used)) static int
tun_busy_locked(struct tuntap_softc *tp)
{

	TUN_LOCK_ASSERT(tp);
	if ((tp->tun_flags & TUN_DYING) != 0) {
		/*
		 * Perhaps unintuitive, but the device is busy going away.
		 * Other interpretations of EBUSY from tun_busy make little
		 * sense, since making a busy device even more busy doesn't
		 * sound like a problem.
		 */
		return (EBUSY);
	}

	++tp->tun_busy;
	return (0);
}