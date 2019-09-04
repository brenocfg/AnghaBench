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
typedef  int /*<<< orphan*/  playerState_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEEPMIND_UPDATE_INVENTORY ; 
 int /*<<< orphan*/  trap_DeepmindCallback (int /*<<< orphan*/ ,intptr_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dmlab_update_inventory(playerState_t* player_state, int is_bot) {
  trap_DeepmindCallback(DEEPMIND_UPDATE_INVENTORY, (intptr_t)player_state,
                        is_bot, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}