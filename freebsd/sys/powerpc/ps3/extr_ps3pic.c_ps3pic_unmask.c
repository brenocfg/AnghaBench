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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int u_int ;
struct ps3pic_softc {int /*<<< orphan*/ * mask_thread1; int /*<<< orphan*/ * mask_thread0; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set_64 (int /*<<< orphan*/ *,unsigned long) ; 
 struct ps3pic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lv1_did_update_interrupt_mask (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lv1_get_logical_ppe_id (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ps3pic_unmask(device_t dev, u_int irq, void *priv)
{
	struct ps3pic_softc *sc;
	uint64_t ppe;

	sc = device_get_softc(dev);
	atomic_set_64(&sc->mask_thread0[0], 1UL << (63 - irq));
	atomic_set_64(&sc->mask_thread1[0], 1UL << (63 - irq));

	lv1_get_logical_ppe_id(&ppe);
	lv1_did_update_interrupt_mask(ppe, 0);
	lv1_did_update_interrupt_mask(ppe, 1);
}