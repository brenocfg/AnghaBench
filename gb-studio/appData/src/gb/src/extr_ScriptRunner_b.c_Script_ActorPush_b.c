#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* UBYTE ;
struct TYPE_8__ {void* y; void* x; } ;
struct TYPE_6__ {int x; int y; } ;
struct TYPE_5__ {void* y; void* x; } ;
struct TYPE_7__ {TYPE_2__ dir; TYPE_1__ pos; } ;

/* Variables and functions */
 void* ACTOR_MAX_X ; 
 void* ACTOR_MAX_Y ; 
 int /*<<< orphan*/  ACTOR_MOVE_ENABLED ; 
 int /*<<< orphan*/  ACTOR_NOCLIP ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_4__ actor_move_dest ; 
 int /*<<< orphan*/  actor_move_settings ; 
 TYPE_3__* actors ; 
 int /*<<< orphan*/  script_action_complete ; 
 size_t script_actor ; 
 scalar_t__* script_cmd_args ; 
 scalar_t__ script_cmd_args_len ; 
 int /*<<< orphan*/  script_ptr ; 

void Script_ActorPush_b()
{
  UBYTE dest_x, dest_y;

  if (script_cmd_args[0])
  {
    if (actors[0].dir.x < 0)
    {
      dest_x = 0;
    }
    else if (actors[0].dir.x > 0)
    {
      dest_x = ACTOR_MAX_X;
    }
    else
    {
      dest_x = actors[script_actor].pos.x;
    }
    if (actors[0].dir.y < 0)
    {
      dest_y = 0;
    }
    else if (actors[0].dir.y > 0)
    {
      dest_y = ACTOR_MAX_Y;
    }
    else
    {
      dest_y = actors[script_actor].pos.y;
    }
  }
  else
  {
    dest_x = actors[script_actor].pos.x + (actors[0].dir.x * 16);
    dest_y = actors[script_actor].pos.y + (actors[0].dir.y * 16);
  }

  actor_move_settings |= ACTOR_MOVE_ENABLED;
  actor_move_settings &= ~ACTOR_NOCLIP;
  actor_move_dest.x = 0; // @wtf-but-needed
  actor_move_dest.x = dest_x;
  actor_move_dest.y = 0; // @wtf-but-needed
  actor_move_dest.y = dest_y;
  // script_ptr += 1 + script_cmd_args_len;
  // script_action_complete = FALSE;

  script_ptr += 1 + script_cmd_args_len;
  script_action_complete = FALSE;
}