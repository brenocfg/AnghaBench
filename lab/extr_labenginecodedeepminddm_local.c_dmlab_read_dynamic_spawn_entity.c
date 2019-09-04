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

/* Variables and functions */
 int /*<<< orphan*/  DEEPMIND_READ_DYNAMIC_SPAWN_ENTITY ; 
 int /*<<< orphan*/  trap_DeepmindCallback (int /*<<< orphan*/ ,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dmlab_read_dynamic_spawn_entity(int entity_index, char* spawn_var_chars,
                                     int* num_spawn_var_chars,
                                     int spawn_var_offsets[][2],
                                     int* num_spawn_vars) {
  trap_DeepmindCallback(DEEPMIND_READ_DYNAMIC_SPAWN_ENTITY,  //
                        (intptr_t)entity_index,
                        (intptr_t)spawn_var_chars,      //
                        (intptr_t)num_spawn_var_chars,  //
                        (intptr_t)spawn_var_offsets,    //
                        (intptr_t)num_spawn_vars, 0, 0, 0, 0, 0, 0, 0);
}