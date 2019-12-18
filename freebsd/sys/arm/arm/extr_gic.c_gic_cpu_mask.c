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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct arm_gic_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GICD_ITARGETSR (int) ; 
 int gic_d_read_4 (struct arm_gic_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t
gic_cpu_mask(struct arm_gic_softc *sc)
{
	uint32_t mask;
	int i;

	/* Read the current cpuid mask by reading ITARGETSR{0..7} */
	for (i = 0; i < 8; i++) {
		mask = gic_d_read_4(sc, GICD_ITARGETSR(4 * i));
		if (mask != 0)
			break;
	}
	/* No mask found, assume we are on CPU interface 0 */
	if (mask == 0)
		return (1);

	/* Collect the mask in the lower byte */
	mask |= mask >> 16;
	mask |= mask >> 8;

	return (mask);
}