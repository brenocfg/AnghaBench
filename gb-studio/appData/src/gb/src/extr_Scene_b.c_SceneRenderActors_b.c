#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ UBYTE ;
typedef  int /*<<< orphan*/  ACTOR ;

/* Variables and functions */
 scalar_t__ ACTOR_ENABLED (scalar_t__*) ; 
 scalar_t__ ACTOR_FLIP (scalar_t__*) ; 
 scalar_t__ ACTOR_FRAME (scalar_t__*) ; 
 scalar_t__ ACTOR_FRAME_OFFSET (scalar_t__*) ; 
 scalar_t__ ACTOR_SPRITE (scalar_t__*) ; 
 scalar_t__ ACTOR_SPRITE_OFFSET ; 
 scalar_t__ ACTOR_X (scalar_t__*) ; 
 scalar_t__ ACTOR_Y (scalar_t__*) ; 
 scalar_t__ IS_FRAME_9 ; 
 scalar_t__ MENU_CLOSED_Y ; 
 scalar_t__ MUL_2 (scalar_t__) ; 
 scalar_t__ MUL_4 (scalar_t__) ; 
 scalar_t__ SCX_REG ; 
 scalar_t__ SCY_REG ; 
 scalar_t__* actors ; 
 int /*<<< orphan*/  move_sprite (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ scene_num_actors ; 
 int /*<<< orphan*/  set_sprite_tile (scalar_t__,scalar_t__) ; 
 scalar_t__ win_pos_x ; 
 scalar_t__ win_pos_y ; 

void SceneRenderActors_b()
{
  UBYTE i, s, x, y, jump;
  UBYTE *ptr;

  if (IS_FRAME_9)
  {
    ptr = actors;
    jump = sizeof(ACTOR);

    for (i = 0; i != scene_num_actors; ++i)
    {
      s = MUL_2(i) + ACTOR_SPRITE_OFFSET;
      x = MUL_4(ACTOR_SPRITE(ptr) + ACTOR_FRAME(ptr) + ACTOR_FRAME_OFFSET(ptr));
      if (ACTOR_FLIP(ptr))
      {
        set_sprite_tile(s + 1, x);
        set_sprite_tile(s, x + 2);
      }
      else
      {
        set_sprite_tile(s, x);
        set_sprite_tile(s + 1, x + 2);
      }

      ptr += jump;
    }
  }

  ptr = actors;
  jump = sizeof(ACTOR);

  for (i = 0; i != scene_num_actors; ++i)
  {
    s = MUL_2(i) + ACTOR_SPRITE_OFFSET;
    x = ACTOR_X(ptr) - SCX_REG;
    y = ACTOR_Y(ptr) - SCY_REG;

    if (ACTOR_ENABLED(ptr) && (win_pos_y == MENU_CLOSED_Y || (y < win_pos_y + 16 || x < win_pos_x + 8)))
    {
      move_sprite(s, x, y);
      move_sprite(s + 1, x + 8, y);
    }
    else
    {
      move_sprite(s, 0, 0);
      move_sprite(s + 1, 0, 0);
    }
    ptr += jump;
  }
}