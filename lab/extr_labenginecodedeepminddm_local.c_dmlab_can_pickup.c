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
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  playerState_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEEPMIND_CAN_PICKUP ; 
 int /*<<< orphan*/  trap_DeepmindCallback (int /*<<< orphan*/ ,intptr_t,intptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

qboolean dmlab_can_pickup(int entity_id, const playerState_t* ps) {
  return trap_DeepmindCallback(DEEPMIND_CAN_PICKUP, (intptr_t)entity_id,
                               (intptr_t)ps, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}