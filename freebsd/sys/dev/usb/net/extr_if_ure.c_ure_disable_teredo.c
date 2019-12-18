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
struct ure_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  URE_MCU_TYPE_PLA ; 
 int URE_OOB_TEREDO_EN ; 
 int /*<<< orphan*/  URE_PLA_REALWOW_TIMER ; 
 int /*<<< orphan*/  URE_PLA_TEREDO_CFG ; 
 int /*<<< orphan*/  URE_PLA_TEREDO_TIMER ; 
 int /*<<< orphan*/  URE_PLA_WDT6_CTRL ; 
 int URE_TEREDO_RS_EVENT_MASK ; 
 int URE_TEREDO_SEL ; 
 int /*<<< orphan*/  URE_WDT6_SET_MODE ; 
 int ure_read_4 (struct ure_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ure_write_2 (struct ure_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ure_write_4 (struct ure_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ure_disable_teredo(struct ure_softc *sc)
{

	ure_write_4(sc, URE_PLA_TEREDO_CFG, URE_MCU_TYPE_PLA,
	    ure_read_4(sc, URE_PLA_TEREDO_CFG, URE_MCU_TYPE_PLA) & 
	    ~(URE_TEREDO_SEL | URE_TEREDO_RS_EVENT_MASK | URE_OOB_TEREDO_EN));
	ure_write_2(sc, URE_PLA_WDT6_CTRL, URE_MCU_TYPE_PLA,
	    URE_WDT6_SET_MODE);
	ure_write_2(sc, URE_PLA_REALWOW_TIMER, URE_MCU_TYPE_PLA, 0);
	ure_write_4(sc, URE_PLA_TEREDO_TIMER, URE_MCU_TYPE_PLA, 0);
}