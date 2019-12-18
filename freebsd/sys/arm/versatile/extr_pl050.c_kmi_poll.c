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
struct kmi_softc {int /*<<< orphan*/  sc_flags; int /*<<< orphan*/  sc_poll_thread; } ;
struct TYPE_3__ {struct kmi_softc* kb_data; } ;
typedef  TYPE_1__ keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  KMI_FLAG_POLLING ; 
 int /*<<< orphan*/  KMI_LOCK () ; 
 int /*<<< orphan*/  KMI_UNLOCK () ; 
 int /*<<< orphan*/  curthread ; 

__attribute__((used)) static int
kmi_poll(keyboard_t *kbd, int on)
{
	struct kmi_softc *sc = kbd->kb_data;

	KMI_LOCK();
	if (on) {
		sc->sc_flags |= KMI_FLAG_POLLING;
		sc->sc_poll_thread = curthread;
	} else {
		sc->sc_flags &= ~KMI_FLAG_POLLING;
	}
	KMI_UNLOCK();

	return (0);
}