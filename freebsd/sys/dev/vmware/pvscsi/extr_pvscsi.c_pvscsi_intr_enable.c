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
typedef  int /*<<< orphan*/  uint32_t ;
struct pvscsi_softc {scalar_t__ use_msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVSCSI_INTR_CMPL_MASK ; 
 int /*<<< orphan*/  PVSCSI_INTR_MSG_MASK ; 
 int /*<<< orphan*/  PVSCSI_REG_OFFSET_INTR_MASK ; 
 int /*<<< orphan*/  pvscsi_reg_write (struct pvscsi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
pvscsi_intr_enable(struct pvscsi_softc *sc)
{
	uint32_t mask;

	mask = PVSCSI_INTR_CMPL_MASK;
	if (sc->use_msg) {
		mask |= PVSCSI_INTR_MSG_MASK;
	}

	pvscsi_reg_write(sc, PVSCSI_REG_OFFSET_INTR_MASK, mask);
}