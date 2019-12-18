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
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct tuntap_softc {TYPE_1__ tun_rsel; } ;
struct knote {struct tuntap_softc* kn_hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  knlist_remove (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tunkqdetach(struct knote *kn)
{
	struct tuntap_softc	*tp = kn->kn_hook;

	knlist_remove(&tp->tun_rsel.si_note, kn, 0);
}