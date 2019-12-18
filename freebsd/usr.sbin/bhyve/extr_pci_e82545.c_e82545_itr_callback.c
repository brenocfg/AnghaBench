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
typedef  int uint32_t ;
struct e82545_softc {int esc_ICR; int esc_IMS; int esc_irq_asserted; int /*<<< orphan*/  esc_mtx; int /*<<< orphan*/ * esc_mevpitr; int /*<<< orphan*/  esc_pi; } ;
typedef  enum ev_type { ____Placeholder_ev_type } ev_type ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 int /*<<< orphan*/  mevent_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_lintr_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
e82545_itr_callback(int fd, enum ev_type type, void *param)
{
	uint32_t new;
	struct e82545_softc *sc = param;

	pthread_mutex_lock(&sc->esc_mtx);
	new = sc->esc_ICR & sc->esc_IMS;
	if (new && !sc->esc_irq_asserted) {
		DPRINTF("itr callback: lintr assert %x\r\n", new);
		sc->esc_irq_asserted = 1;
		pci_lintr_assert(sc->esc_pi);
	} else {
		mevent_delete(sc->esc_mevpitr);
		sc->esc_mevpitr = NULL;
	}
	pthread_mutex_unlock(&sc->esc_mtx);
}