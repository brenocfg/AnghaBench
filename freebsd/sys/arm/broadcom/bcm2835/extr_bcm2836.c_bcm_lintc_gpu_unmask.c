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
struct bcm_lintc_softc {int dummy; } ;
struct bcm_lintc_irqsrc {int /*<<< orphan*/  bli_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_LINTC_GPU_ROUTING_REG ; 
 int /*<<< orphan*/  bcm_lintc_write_4 (struct bcm_lintc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
bcm_lintc_gpu_unmask(struct bcm_lintc_softc *sc, struct bcm_lintc_irqsrc *bli)
{

	/* It's accessed just and only by one core. */
	bcm_lintc_write_4(sc, BCM_LINTC_GPU_ROUTING_REG, bli->bli_value);
}