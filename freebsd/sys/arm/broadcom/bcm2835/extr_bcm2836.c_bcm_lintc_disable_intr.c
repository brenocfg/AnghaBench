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
struct intr_irqsrc {int dummy; } ;
struct bcm_lintc_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_lintc_mask (int /*<<< orphan*/ ,struct bcm_lintc_irqsrc*) ; 
 int /*<<< orphan*/  device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bcm_lintc_disable_intr(device_t dev, struct intr_irqsrc *isrc)
{

	bcm_lintc_mask(device_get_softc(dev), (struct bcm_lintc_irqsrc *)isrc);
}