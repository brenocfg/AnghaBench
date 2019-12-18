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
struct malo_hal {int mh_cmdaddr; int /*<<< orphan*/  mh_dmamap; int /*<<< orphan*/  mh_dmat; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int MALO_H2ARIC_BIT_DOOR_BELL ; 
 int /*<<< orphan*/  MALO_REG_GEN_PTR ; 
 int /*<<< orphan*/  MALO_REG_H2A_INTERRUPT_EVENTS ; 
 int /*<<< orphan*/  MALO_REG_INT_CODE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malo_hal_read4 (struct malo_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malo_hal_write4 (struct malo_hal*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
malo_hal_trigger_pcicmd(struct malo_hal *mh)
{
	uint32_t dummy;

	bus_dmamap_sync(mh->mh_dmat, mh->mh_dmamap, BUS_DMASYNC_PREWRITE);

	malo_hal_write4(mh, MALO_REG_GEN_PTR, mh->mh_cmdaddr);
	dummy = malo_hal_read4(mh, MALO_REG_INT_CODE);

	malo_hal_write4(mh, MALO_REG_INT_CODE, 0x00);
	dummy = malo_hal_read4(mh, MALO_REG_INT_CODE);

	malo_hal_write4(mh, MALO_REG_H2A_INTERRUPT_EVENTS,
	    MALO_H2ARIC_BIT_DOOR_BELL);
	dummy = malo_hal_read4(mh, MALO_REG_INT_CODE);
}