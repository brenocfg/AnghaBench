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
struct TYPE_2__ {int /*<<< orphan*/  board_flags; } ;
struct bhnd_pmu_softc {TYPE_1__ board; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_BFL_BUCKBOOST ; 
 int BHND_PMU_GET_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
bhnd_pmu_res_depfltr_bb(struct bhnd_pmu_softc *sc)
{	
	return (BHND_PMU_GET_FLAG(sc->board.board_flags, BHND_BFL_BUCKBOOST));
}