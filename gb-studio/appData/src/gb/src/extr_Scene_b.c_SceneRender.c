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
 int /*<<< orphan*/  SceneRenderActors_b () ; 
 int /*<<< orphan*/  SceneRenderCameraShake_b () ; 
 int /*<<< orphan*/  SceneRenderEmoteBubble_b () ; 

void SceneRender()
{
  SceneRenderCameraShake_b();
  SceneRenderActors_b();
  SceneRenderEmoteBubble_b();
}