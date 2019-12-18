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

/* Variables and functions */
 int /*<<< orphan*/  BUBBLE_SPRITE_LEFT ; 
 scalar_t__ BUBBLE_TOTAL_FRAMES ; 
 scalar_t__ emote_timer ; 
 int /*<<< orphan*/  hide_sprite_pair (int /*<<< orphan*/ ) ; 

void SceneUpdateEmoteBubble_b()
{
  // If should be showing emote bubble
  if (emote_timer != 0)
  {
    // If reached end of timer
    if (emote_timer == BUBBLE_TOTAL_FRAMES)
    {
      // Reset the timer
      emote_timer = 0;

      // Hide the bubble sprites
      hide_sprite_pair(BUBBLE_SPRITE_LEFT);
    }
    else
    {
      // Inc timer
      emote_timer++;
    }
  }
}