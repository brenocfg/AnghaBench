#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UWORD ;
typedef  int UBYTE ;
struct TYPE_5__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_4__ {int x; int y; } ;
struct TYPE_6__ {TYPE_2__ dir; TYPE_1__ pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLE_RAM ; 
 int /*<<< orphan*/  ENABLE_RAM ; 
 size_t NUM_VARIABLES ; 
 int* RAMPtr ; 
 scalar_t__ RAM_START_PTR ; 
 scalar_t__ RAM_START_VARS_PTR ; 
 void* TRUE ; 
 TYPE_3__* actors ; 
 int map_next_sprite ; 
 int scene_index ; 
 scalar_t__ script_cmd_args_len ; 
 void* script_continue ; 
 int /*<<< orphan*/  script_ptr ; 
 int* script_variables ; 

void Script_SaveData_b()
{
  UWORD i;

  ENABLE_RAM;

  RAMPtr = (UBYTE *)RAM_START_PTR;
  RAMPtr[0] = TRUE; // Flag to determine if data has been stored

  // Save current scene
  RAMPtr[1] = scene_index;

  // Save player position
  RAMPtr[2] = actors[0].pos.x;
  RAMPtr[3] = actors[0].pos.y;
  if (actors[0].dir.x < 0)
  {
    RAMPtr[4] = 2;
  }
  else if (actors[0].dir.x > 0)
  {
    RAMPtr[4] = 4;
  }
  else if (actors[0].dir.y < 0)
  {
    RAMPtr[4] = 8;
  }
  else
  {
    RAMPtr[4] = 1;
  }

  // Save player sprite
  RAMPtr[5] = map_next_sprite;

  // Save variable values
  RAMPtr = (UBYTE *)RAM_START_VARS_PTR;
  for (i = 0; i < NUM_VARIABLES; i++)
  {
    RAMPtr[i] = script_variables[i];
  }

  DISABLE_RAM;

  script_ptr += 1 + script_cmd_args_len;
  script_continue = TRUE;
}