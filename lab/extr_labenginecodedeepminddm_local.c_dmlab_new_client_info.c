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
 int /*<<< orphan*/  DEEPMIND_NEW_CLIENT_INFO ; 
 int /*<<< orphan*/  trap_DeepmindCallback (int /*<<< orphan*/ ,intptr_t,intptr_t,intptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dmlab_new_client_info(int player_idx, const char* player_name,
                           const char* player_model) {
  trap_DeepmindCallback(DEEPMIND_NEW_CLIENT_INFO, (intptr_t)player_idx,
                        (intptr_t)player_name, (intptr_t)player_model, 0, 0, 0,
                        0, 0, 0, 0, 0, 0);
}