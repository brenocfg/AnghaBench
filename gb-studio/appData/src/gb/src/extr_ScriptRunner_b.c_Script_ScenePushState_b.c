#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int x; int y; } ;
struct TYPE_8__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_12__ {TYPE_4__ pos; TYPE_2__ dir; } ;
struct TYPE_9__ {int x; int y; } ;
struct TYPE_7__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_11__ {TYPE_3__ player_pos; TYPE_1__ player_dir; int /*<<< orphan*/  scene_index; } ;

/* Variables and functions */
 size_t MAX_SCENE_STATES ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_6__* actors ; 
 int /*<<< orphan*/  scene_index ; 
 TYPE_5__* scene_stack ; 
 size_t scene_stack_ptr ; 
 scalar_t__ script_cmd_args_len ; 
 int /*<<< orphan*/  script_continue ; 
 int /*<<< orphan*/  script_ptr ; 

void Script_ScenePushState_b()
{
  if (scene_stack_ptr < MAX_SCENE_STATES)
  {
    scene_stack[scene_stack_ptr].scene_index = scene_index;
    scene_stack[scene_stack_ptr].player_dir.x = actors[0].dir.x;
    scene_stack[scene_stack_ptr].player_dir.y = actors[0].dir.y;
    scene_stack[scene_stack_ptr].player_pos.x = 0; // @wtf-but-needed
    scene_stack[scene_stack_ptr].player_pos.x = actors[0].pos.x >> 3;
    scene_stack[scene_stack_ptr].player_pos.y = 0; // @wtf-but-needed
    scene_stack[scene_stack_ptr].player_pos.y = actors[0].pos.y >> 3;
    scene_stack_ptr++;
  }

  script_ptr += 1 + script_cmd_args_len;
  script_continue = TRUE;
}