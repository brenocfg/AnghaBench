#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * wcbbase; int /*<<< orphan*/  rxdesc_read; } ;
struct TYPE_3__ {int /*<<< orphan*/ * wcbbase; int /*<<< orphan*/  rxdesc_write; int /*<<< orphan*/  rxdesc_read; } ;
struct malo_softc {TYPE_2__ malo_hwdma; TYPE_1__ malo_hwspecs; } ;

/* Variables and functions */
 int MALO_NUM_TX_QUEUES ; 
 int /*<<< orphan*/  malo_bar0_write4 (struct malo_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
malo_hal_set_rxtxdma(struct malo_softc *sc)
{
	int i;

	malo_bar0_write4(sc, sc->malo_hwspecs.rxdesc_read,
	    sc->malo_hwdma.rxdesc_read);
	malo_bar0_write4(sc, sc->malo_hwspecs.rxdesc_write,
	    sc->malo_hwdma.rxdesc_read);

	for (i = 0; i < MALO_NUM_TX_QUEUES; i++) {
		malo_bar0_write4(sc,
		    sc->malo_hwspecs.wcbbase[i], sc->malo_hwdma.wcbbase[i]);
	}
}