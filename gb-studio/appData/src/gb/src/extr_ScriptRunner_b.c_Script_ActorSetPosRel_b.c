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
struct TYPE_3__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_4__ {TYPE_1__ pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* actors ; 
 size_t script_actor ; 
 int* script_cmd_args ; 
 scalar_t__ script_cmd_args_len ; 
 int /*<<< orphan*/  script_continue ; 
 int /*<<< orphan*/  script_ptr ; 

void Script_ActorSetPosRel_b()
{
  if (script_cmd_args[0] != 0)
  {
    if (script_cmd_args[1])
    {
      actors[script_actor].pos.x = actors[script_actor].pos.x - (script_cmd_args[0] << 3);
    }
    else
    {
      actors[script_actor].pos.x = actors[script_actor].pos.x + (script_cmd_args[0] << 3);
    }
  }

  if (script_cmd_args[2] != 0)
  {
    if (script_cmd_args[3])
    {
      actors[script_actor].pos.y = actors[script_actor].pos.y - (script_cmd_args[2] << 3);
    }
    else
    {
      actors[script_actor].pos.y = actors[script_actor].pos.y + (script_cmd_args[2] << 3);
    }
  }

  script_ptr += 1 + script_cmd_args_len;
  script_continue = TRUE;
}