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

/* Variables and functions */
 int /*<<< orphan*/  DEEPMIND_REWARD_OVERRIDE ; 
 int trap_DeepmindCallback (int /*<<< orphan*/ ,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,intptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int dmlab_reward_override(const char* reason_opt, int player_id, int team,
                          const int* other_player_id_opt,
                          const vec3_t origin_opt, int score) {
  return trap_DeepmindCallback(
      DEEPMIND_REWARD_OVERRIDE, (intptr_t)reason_opt, (intptr_t)player_id,
      (intptr_t)team, (intptr_t)other_player_id_opt, (intptr_t)origin_opt,
      (intptr_t)score, 0, 0, 0, 0, 0, 0);
}