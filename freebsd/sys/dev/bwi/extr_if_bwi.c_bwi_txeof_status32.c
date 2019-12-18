#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct bwi_softc {TYPE_1__* sc_txstats; } ;
struct bwi_desc32 {int dummy; } ;
struct TYPE_2__ {scalar_t__ stats_ctrl_base; } ;

/* Variables and functions */
 scalar_t__ BWI_RX32_INDEX ; 
 scalar_t__ BWI_RX32_STATUS ; 
 int /*<<< orphan*/  BWI_RX32_STATUS_INDEX_MASK ; 
 scalar_t__ CSR_READ_4 (struct bwi_softc*,scalar_t__) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct bwi_softc*,scalar_t__,int) ; 
 int __SHIFTOUT (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwi_start_locked (struct bwi_softc*) ; 
 int /*<<< orphan*/  bwi_txeof_status (struct bwi_softc*,int) ; 

__attribute__((used)) static void
bwi_txeof_status32(struct bwi_softc *sc)
{
	uint32_t val, ctrl_base;
	int end_idx;

	ctrl_base = sc->sc_txstats->stats_ctrl_base;

	val = CSR_READ_4(sc, ctrl_base + BWI_RX32_STATUS);
	end_idx = __SHIFTOUT(val, BWI_RX32_STATUS_INDEX_MASK) /
		  sizeof(struct bwi_desc32);

	bwi_txeof_status(sc, end_idx);

	CSR_WRITE_4(sc, ctrl_base + BWI_RX32_INDEX,
		    end_idx * sizeof(struct bwi_desc32));

	bwi_start_locked(sc);
}