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
typedef  scalar_t__ UBYTE ;
struct TYPE_3__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_4__ {TYPE_1__ pos; } ;

/* Variables and functions */
 scalar_t__ ACTOR_HEIGHT ; 
 size_t BUBBLE_ANIMATION_FRAMES ; 
 int /*<<< orphan*/  BUBBLE_SPRITE_LEFT ; 
 size_t BUBBLE_TOTAL_FRAMES ; 
 scalar_t__ SCX_REG ; 
 scalar_t__ SCY_REG ; 
 TYPE_2__* actors ; 
 size_t emote_actor ; 
 scalar_t__* emote_offsets ; 
 size_t emote_timer ; 
 int /*<<< orphan*/  move_sprite_pair (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

void SceneRenderEmoteBubble_b()
{
  UBYTE screen_x, screen_y;

  // If should be showing emote bubble
  if (emote_timer != 0)
  {
    // If reached end of timer
    if (emote_timer != BUBBLE_TOTAL_FRAMES)
    {

      // Set x and y above actor displaying emote
      screen_x = actors[emote_actor].pos.x - SCX_REG;
      screen_y = actors[emote_actor].pos.y - ACTOR_HEIGHT - SCY_REG;

      // At start of animation bounce bubble in using stored offsets
      if (emote_timer < BUBBLE_ANIMATION_FRAMES)
      {
        screen_y += emote_offsets[emote_timer];
      }

      // Reposition sprites (left and right)
      move_sprite_pair(BUBBLE_SPRITE_LEFT, screen_x, screen_y);
    }
  }
}