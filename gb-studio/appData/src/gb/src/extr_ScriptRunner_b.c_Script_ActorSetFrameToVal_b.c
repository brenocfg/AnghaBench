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
struct TYPE_2__ {int frame; int frames_len; scalar_t__ flip; } ;

/* Variables and functions */
 int /*<<< orphan*/  SceneRenderActor (size_t) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* actors ; 
 size_t script_actor ; 
 int* script_cmd_args ; 
 scalar_t__ script_cmd_args_len ; 
 int /*<<< orphan*/  script_continue ; 
 int /*<<< orphan*/  script_ptr ; 
 int* script_variables ; 

void Script_ActorSetFrameToVal_b()
{
  actors[script_actor].frame = 0;
  actors[script_actor].flip = 0;
  actors[script_actor].frame = script_variables[(script_cmd_args[0] * 256) + script_cmd_args[1]] % actors[script_actor].frames_len;
  SceneRenderActor(script_actor);
  script_ptr += 1 + script_cmd_args_len;
  script_continue = TRUE;
}