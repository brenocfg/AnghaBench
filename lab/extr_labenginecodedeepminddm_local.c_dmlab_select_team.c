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
 int /*<<< orphan*/  DEEPMIND_TEAM_SELECT ; 
 scalar_t__ trap_DeepmindCallback (int /*<<< orphan*/ ,intptr_t,intptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char dmlab_select_team(int player_id, const char* player_name) {
  return (char)trap_DeepmindCallback(DEEPMIND_TEAM_SELECT, (intptr_t)player_id,
                                     (intptr_t)player_name, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0);
}