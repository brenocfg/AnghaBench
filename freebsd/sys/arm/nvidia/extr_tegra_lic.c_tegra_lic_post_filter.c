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
struct tegra_lic_sc {int /*<<< orphan*/  parent; } ;
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PIC_POST_FILTER (int /*<<< orphan*/ ,struct intr_irqsrc*) ; 
 struct tegra_lic_sc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tegra_lic_post_filter(device_t dev, struct intr_irqsrc *isrc)
{
	struct tegra_lic_sc *sc = device_get_softc(dev);

	PIC_POST_FILTER(sc->parent, isrc);
}