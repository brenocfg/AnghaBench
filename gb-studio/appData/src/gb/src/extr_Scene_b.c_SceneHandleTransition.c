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
 int /*<<< orphan*/  IsFading () ; 
 int /*<<< orphan*/  SceneInit () ; 
 scalar_t__ scene_index ; 
 scalar_t__ scene_next_index ; 

void SceneHandleTransition()
{
  // If scene has switched and FadeOut is complete
  if (scene_index != scene_next_index && !IsFading())
  {
    scene_index = scene_next_index;
    SceneInit();
  }
}