#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  board_flags; } ;
struct TYPE_3__ {scalar_t__ chip_id; int chip_rev; } ;
struct bhnd_pmu_softc {TYPE_2__ board; TYPE_1__ cid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_BFL_NOCBUCK ; 
 scalar_t__ BHND_CHIPID_BCM4325 ; 
 int BHND_PMU_GET_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
bhnd_pmu_res_depfltr_ncb(struct bhnd_pmu_softc *sc)
{
	if (sc->cid.chip_id == BHND_CHIPID_BCM4325 && sc->cid.chip_rev <= 1)
		return (false);

	return (BHND_PMU_GET_FLAG(sc->board.board_flags, BHND_BFL_NOCBUCK));
}