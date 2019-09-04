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
typedef  scalar_t__ vec3_t ;
typedef  scalar_t__ qboolean ;
typedef  int /*<<< orphan*/  playerState_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEEPMIND_OVERRIDE_LOOKAT ; 
 int /*<<< orphan*/  trap_DeepmindCallback (int /*<<< orphan*/ ,intptr_t,intptr_t,intptr_t,intptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dmlab_trigger_lookat(int entity_id, qboolean looked_at, vec3_t position,
                          const playerState_t* ps) {
  trap_DeepmindCallback(DEEPMIND_OVERRIDE_LOOKAT,
                        (intptr_t)entity_id, (intptr_t)looked_at,
                        (intptr_t)position,
                        (intptr_t)ps, 0, 0, 0, 0, 0, 0, 0, 0);
}