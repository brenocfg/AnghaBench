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
struct mv_ap806_gicp_softc {int /*<<< orphan*/  parent; } ;
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PIC_ENABLE_INTR (int /*<<< orphan*/ ,struct intr_irqsrc*) ; 
 struct mv_ap806_gicp_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mv_ap806_gicp_enable_intr(device_t dev, struct intr_irqsrc *isrc)
{
	struct mv_ap806_gicp_softc *sc;

	sc = device_get_softc(dev);

	PIC_ENABLE_INTR(sc->parent, isrc);
}