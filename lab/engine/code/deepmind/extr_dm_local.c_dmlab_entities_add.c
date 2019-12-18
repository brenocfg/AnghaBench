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
 int /*<<< orphan*/  DEEPMIND_ENTITIES_ADD ; 
 int /*<<< orphan*/  trap_DeepmindCallback (int /*<<< orphan*/ ,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dmlab_entities_add(int entity_id, int user_id, int type, int flags,
                           float position[3], const char* classname) {
  trap_DeepmindCallback(DEEPMIND_ENTITIES_ADD, (intptr_t)entity_id,
                        (intptr_t)user_id, (intptr_t)type, (intptr_t)flags,
                        (intptr_t)position, (intptr_t)classname, 0, 0, 0, 0, 0,
                        0);
}