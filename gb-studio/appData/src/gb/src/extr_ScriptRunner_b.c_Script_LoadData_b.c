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
typedef  size_t UWORD ;
typedef  int UBYTE ;
struct TYPE_4__ {int x; int y; } ;
struct TYPE_3__ {int x; int y; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLE_RAM ; 
 int /*<<< orphan*/  ENABLE_RAM ; 
 void* FALSE ; 
 int /*<<< orphan*/  FadeOut () ; 
 int /*<<< orphan*/  FadeSetSpeed (int) ; 
 size_t NUM_VARIABLES ; 
 int* RAMPtr ; 
 scalar_t__ RAM_START_PTR ; 
 scalar_t__ RAM_START_VARS_PTR ; 
 int /*<<< orphan*/  SCENE ; 
 int TRUE ; 
 TYPE_2__ map_next_dir ; 
 TYPE_1__ map_next_pos ; 
 int map_next_sprite ; 
 int scene_index ; 
 void* scene_loaded ; 
 int scene_next_index ; 
 void* script_action_complete ; 
 scalar_t__ script_cmd_args_len ; 
 int /*<<< orphan*/  script_ptr ; 
 int* script_variables ; 
 int /*<<< orphan*/  stage_next_type ; 

void Script_LoadData_b()
{
  UWORD i;

  ENABLE_RAM;

  RAMPtr = (UBYTE *)RAM_START_PTR;
  if (*RAMPtr == TRUE)
  {
    // Set scene index
    RAMPtr++;
    scene_next_index = *RAMPtr;
    scene_index = scene_next_index + 1;

    // Position player
    RAMPtr++;
    map_next_pos.x = 0; // @wtf-but-needed
    map_next_pos.x = *RAMPtr;
    RAMPtr++;
    map_next_pos.y = 0; // @wtf-but-needed
    map_next_pos.y = *RAMPtr;
    RAMPtr++;
    map_next_dir.x = *RAMPtr == 2 ? -1 : *RAMPtr == 4 ? 1 : 0;
    map_next_dir.y = *RAMPtr == 8 ? -1 : *RAMPtr == 1 ? 1 : 0;

    // Load player sprite
    RAMPtr++;
    map_next_sprite = *RAMPtr;

    // Load variable values
    RAMPtr = (UBYTE *)RAM_START_VARS_PTR;
    for (i = 0; i < NUM_VARIABLES; i++)
    {
      script_variables[i] = RAMPtr[i];
    }

    // Switch to next scene
    stage_next_type = SCENE;
    scene_loaded = FALSE;
    FadeSetSpeed(2);
    FadeOut();

    script_action_complete = FALSE;
  }

  DISABLE_RAM;

  script_ptr += 1 + script_cmd_args_len;
}