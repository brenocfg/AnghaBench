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
struct da8xx_mstpri_board_priorities {int /*<<< orphan*/  board; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct da8xx_mstpri_board_priorities*) ; 
 struct da8xx_mstpri_board_priorities* da8xx_mstpri_board_confs ; 
 scalar_t__ of_machine_is_compatible (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct da8xx_mstpri_board_priorities *
da8xx_mstpri_get_board_prio(void)
{
	const struct da8xx_mstpri_board_priorities *board_prio;
	int i;

	for (i = 0; i < ARRAY_SIZE(da8xx_mstpri_board_confs); i++) {
		board_prio = &da8xx_mstpri_board_confs[i];

		if (of_machine_is_compatible(board_prio->board))
			return board_prio;
	}

	return NULL;
}