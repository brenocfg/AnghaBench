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
struct mv_ap806_sei_softc {int dummy; } ;
struct mv_ap806_sei_irqsrc {int dummy; } ;
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct mv_ap806_sei_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_ap806_sei_isrc_mask (struct mv_ap806_sei_softc*,struct mv_ap806_sei_irqsrc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mv_ap806_sei_enable_intr(device_t dev, struct intr_irqsrc *isrc)
{
	struct mv_ap806_sei_softc *sc;
	struct mv_ap806_sei_irqsrc *sisrc;

	sc = device_get_softc(dev);
	sisrc = (struct mv_ap806_sei_irqsrc *)isrc;
	mv_ap806_sei_isrc_mask(sc, sisrc, 0);
}