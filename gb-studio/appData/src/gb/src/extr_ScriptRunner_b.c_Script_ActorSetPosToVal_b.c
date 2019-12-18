#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int x; int y; } ;
struct TYPE_4__ {TYPE_1__ pos; } ;

/* Variables and functions */
 int ACTOR_MAX_Y ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* actors ; 
 size_t script_actor ; 
 scalar_t__ script_cmd_args_len ; 
 int /*<<< orphan*/  script_continue ; 
 int /*<<< orphan*/  script_ptr ; 
 size_t script_ptr_x ; 
 size_t script_ptr_y ; 
 int* script_variables ; 

void Script_ActorSetPosToVal_b()
{
  actors[script_actor].pos.x = 0; // @wtf-but-needed
  actors[script_actor].pos.x = (script_variables[script_ptr_x] << 3) + 8;
  actors[script_actor].pos.y = 0; // @wtf-but-needed
  actors[script_actor].pos.y = (script_variables[script_ptr_y] << 3) + 8;
  if (script_variables[script_ptr_y] == 31)
  {
    actors[script_actor].pos.y = ACTOR_MAX_Y;
  }
  script_ptr += 1 + script_cmd_args_len;
  script_continue = TRUE;
}