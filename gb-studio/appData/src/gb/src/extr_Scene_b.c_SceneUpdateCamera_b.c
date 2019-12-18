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
typedef  void* UBYTE ;
struct TYPE_4__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_6__ {TYPE_1__ pos; } ;
struct TYPE_5__ {scalar_t__ x; scalar_t__ y; } ;

/* Variables and functions */
 int CAMERA_LOCK_FLAG ; 
 int CAMERA_TRANSITION_FLAG ; 
 void* ClampUBYTE (int /*<<< orphan*/ ,void*,void*) ; 
 void* MUL_8 (int /*<<< orphan*/ ) ; 
 void* SCREEN_HEIGHT_HALF ; 
 void* SCREEN_WIDTH_HALF ; 
 scalar_t__ SCX_REG ; 
 scalar_t__ SCY_REG ; 
 TYPE_3__* actors ; 
 TYPE_2__ camera_dest ; 
 int camera_moved ; 
 int camera_settings ; 
 int camera_speed ; 
 int /*<<< orphan*/  scene_height ; 
 int /*<<< orphan*/  scene_width ; 
 int time ; 

void SceneUpdateCamera_b()
{
  UBYTE cam_x, cam_y;

  // If camera is locked to player
  if ((camera_settings & CAMERA_LOCK_FLAG) == CAMERA_LOCK_FLAG)
  {
    // Reposition based on player position
    cam_x = ClampUBYTE(actors[0].pos.x, SCREEN_WIDTH_HALF, MUL_8(scene_width) - SCREEN_WIDTH_HALF);
    camera_dest.x = cam_x - SCREEN_WIDTH_HALF;
    cam_y = ClampUBYTE(actors[0].pos.y, SCREEN_HEIGHT_HALF, MUL_8(scene_height) - SCREEN_HEIGHT_HALF);
    camera_dest.y = cam_y - SCREEN_HEIGHT_HALF;
  }

  camera_moved = SCX_REG != camera_dest.x || SCY_REG != camera_dest.y;

  if (camera_moved)
  {
    // If camera is animating move towards location
    if ((camera_settings & CAMERA_TRANSITION_FLAG) == CAMERA_TRANSITION_FLAG)
    {
      if ((time & camera_speed) == 0)
      {
        if (SCX_REG > camera_dest.x)
        {
          SCX_REG--;
        }
        else if (SCX_REG < camera_dest.x)
        {
          SCX_REG++;
        }
        if (SCY_REG > camera_dest.y)
        {
          SCY_REG--;
        }
        else if (SCY_REG < camera_dest.y)
        {
          SCY_REG++;
        }
      }
    }
    // Otherwise jump imediately to camera destination
    else
    {
      SCX_REG = camera_dest.x;
      SCY_REG = camera_dest.y;
    }
  }
}