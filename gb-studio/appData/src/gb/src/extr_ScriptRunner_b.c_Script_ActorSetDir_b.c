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
struct TYPE_4__ {TYPE_1__ dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  SceneRenderActor (size_t) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* actors ; 
 size_t script_actor ; 
 int* script_cmd_args ; 
 scalar_t__ script_cmd_args_len ; 
 int /*<<< orphan*/  script_continue ; 
 int /*<<< orphan*/  script_ptr ; 

void Script_ActorSetDir_b()
{
  actors[script_actor].dir.x = script_cmd_args[0] == 2 ? -1 : script_cmd_args[0] == 4 ? 1 : 0;
  actors[script_actor].dir.y = script_cmd_args[0] == 8 ? -1 : script_cmd_args[0] == 1 ? 1 : 0;
  SceneRenderActor(script_actor);
  script_ptr += 1 + script_cmd_args_len;
  script_continue = TRUE;
}