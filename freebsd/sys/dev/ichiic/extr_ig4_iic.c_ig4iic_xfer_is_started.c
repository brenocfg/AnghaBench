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
typedef  int /*<<< orphan*/  ig4iic_softc_t ;

/* Variables and functions */
 int IG4_INTR_START_DET ; 
 int IG4_INTR_STOP_DET ; 
 int /*<<< orphan*/  IG4_REG_RAW_INTR_STAT ; 
 int reg_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ig4iic_xfer_is_started(ig4iic_softc_t *sc)
{
	/*
	 * It requires that no IG4_REG_CLR_INTR or IG4_REG_CLR_START/STOP_DET
	 * register reads is issued after START condition.
	 */
	return ((reg_read(sc, IG4_REG_RAW_INTR_STAT) &
	    (IG4_INTR_START_DET | IG4_INTR_STOP_DET)) == IG4_INTR_START_DET);
}