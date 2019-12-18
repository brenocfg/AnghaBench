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
typedef  int UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  SceneRenderActor_b (int) ; 
 int scene_num_actors ; 

void SceneInit_b4()
{
  UBYTE i;
  for (i = 1; i != scene_num_actors; ++i)
  {
    SceneRenderActor_b(i);
  }
}