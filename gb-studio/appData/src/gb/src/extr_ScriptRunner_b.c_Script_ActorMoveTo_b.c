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
struct TYPE_2__ {int x; int y; } ;

/* Variables and functions */
 int ACTOR_MAX_Y ; 
 int /*<<< orphan*/  ACTOR_MOVE_ENABLED ; 
 int /*<<< orphan*/  ACTOR_NOCLIP ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__ actor_move_dest ; 
 int /*<<< orphan*/  actor_move_settings ; 
 int /*<<< orphan*/  script_action_complete ; 
 int* script_cmd_args ; 
 scalar_t__ script_cmd_args_len ; 
 int /*<<< orphan*/  script_ptr ; 

void Script_ActorMoveTo_b()
{
  actor_move_settings |= ACTOR_MOVE_ENABLED;
  actor_move_settings |= ACTOR_NOCLIP;
  actor_move_dest.x = 0; // @wtf-but-needed
  actor_move_dest.x = (script_cmd_args[0] << 3) + 8;
  actor_move_dest.y = 0; // @wtf-but-needed
  actor_move_dest.y = (script_cmd_args[1] << 3) + 8;
  if (script_cmd_args[1] == 31)
  {
    actor_move_dest.y = ACTOR_MAX_Y;
  }
  script_ptr += 1 + script_cmd_args_len;
  script_action_complete = FALSE;
}