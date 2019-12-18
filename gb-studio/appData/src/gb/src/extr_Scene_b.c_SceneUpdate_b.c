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
 int /*<<< orphan*/  SceneHandleInput () ; 
 int /*<<< orphan*/  SceneHandleTransition () ; 
 int /*<<< orphan*/  SceneHandleTriggers_b () ; 
 int /*<<< orphan*/  SceneHandleWait () ; 
 int /*<<< orphan*/  SceneRender () ; 
 int /*<<< orphan*/  SceneUpdateActors_b () ; 
 int /*<<< orphan*/  SceneUpdateCameraShake_b () ; 
 int /*<<< orphan*/  SceneUpdateCamera_b () ; 
 int /*<<< orphan*/  SceneUpdateEmoteBubble_b () ; 
 int /*<<< orphan*/  SceneUpdateTimer_b () ; 
 int /*<<< orphan*/  ScriptRunnerUpdate () ; 
 int /*<<< orphan*/  UIUpdate () ; 

void SceneUpdate_b()
{
  SceneUpdateCameraShake_b();
  SceneUpdateCamera_b();
  SceneRender();
  SceneUpdateTimer_b();
  SceneHandleInput();
  ScriptRunnerUpdate();
  SceneUpdateActors_b();
  SceneUpdateEmoteBubble_b();
  SceneHandleWait();
  SceneHandleTransition();
  UIUpdate();
  SceneHandleTriggers_b();
}