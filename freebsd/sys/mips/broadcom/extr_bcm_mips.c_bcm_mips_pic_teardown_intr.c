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
struct resource {int dummy; } ;
struct intr_map_data {int dummy; } ;
struct intr_irqsrc {int dummy; } ;
struct bcm_mips_softc {int dummy; } ;
struct bcm_mips_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_MIPS_LOCK (struct bcm_mips_softc*) ; 
 int /*<<< orphan*/  BCM_MIPS_UNLOCK (struct bcm_mips_softc*) ; 
 int bcm_mips_release_cpu_intr (struct bcm_mips_softc*,struct bcm_mips_irqsrc*,struct resource*) ; 
 struct bcm_mips_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcm_mips_pic_teardown_intr(device_t dev, struct intr_irqsrc *irqsrc,
    struct resource *res, struct intr_map_data *data)
{
	struct bcm_mips_softc	*sc;
	struct bcm_mips_irqsrc	*isrc;
	int			 error;

	sc = device_get_softc(dev);
	isrc = (struct bcm_mips_irqsrc *)irqsrc;

	/* Release the CPU interrupt */
	BCM_MIPS_LOCK(sc);
	error = bcm_mips_release_cpu_intr(sc, isrc, res);
	BCM_MIPS_UNLOCK(sc);

	return (error);
}