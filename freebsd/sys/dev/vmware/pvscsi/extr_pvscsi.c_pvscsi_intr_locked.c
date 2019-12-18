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
struct pvscsi_softc {scalar_t__ use_msg; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int PVSCSI_INTR_ALL_SUPPORTED ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvscsi_process_cmp_ring (struct pvscsi_softc*) ; 
 int /*<<< orphan*/  pvscsi_process_msg_ring (struct pvscsi_softc*) ; 
 int pvscsi_read_intr_status (struct pvscsi_softc*) ; 
 int /*<<< orphan*/  pvscsi_write_intr_status (struct pvscsi_softc*,int) ; 

__attribute__((used)) static void
pvscsi_intr_locked(struct pvscsi_softc *sc)
{
	uint32_t val;

	mtx_assert(&sc->lock, MA_OWNED);

	val = pvscsi_read_intr_status(sc);

	if ((val & PVSCSI_INTR_ALL_SUPPORTED) != 0) {
		pvscsi_write_intr_status(sc, val & PVSCSI_INTR_ALL_SUPPORTED);
		pvscsi_process_cmp_ring(sc);
		if (sc->use_msg) {
			pvscsi_process_msg_ring(sc);
		}
	}
}