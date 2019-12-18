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
typedef  int /*<<< orphan*/  UBYTE ;

/* Variables and functions */
 int CAMERA_LOCK_FLAG ; 
 int CAMERA_TRANSITION_FLAG ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IsFading () ; 
 scalar_t__ SceneAwaitInputPressed () ; 
 scalar_t__ SceneCameraAtDest () ; 
 int /*<<< orphan*/  SceneIsEmoting () ; 
 scalar_t__ Script_ActorSetEmote_b ; 
 scalar_t__ Script_AwaitInput_b ; 
 scalar_t__ Script_CameraLock_b ; 
 scalar_t__ Script_CameraMoveTo_b ; 
 scalar_t__ Script_Choice_b ; 
 scalar_t__ Script_FadeIn_b ; 
 scalar_t__ Script_FadeOut_b ; 
 scalar_t__ Script_LoadData_b ; 
 scalar_t__ Script_LoadScene_b ; 
 scalar_t__ Script_OverlayMoveTo_b ; 
 scalar_t__ Script_ScenePopAllState_b ; 
 scalar_t__ Script_ScenePopState_b ; 
 scalar_t__ Script_TextMenu_b ; 
 scalar_t__ Script_TextWithAvatar_b ; 
 scalar_t__ Script_Text_b ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ UIAtDest () ; 
 scalar_t__ UIIsClosed () ; 
 int camera_settings ; 
 scalar_t__ last_fn ; 

UBYTE ScriptLastFnComplete()
{
  UBYTE fading = IsFading();

  if (last_fn == Script_FadeIn_b && !fading)
  {
    return TRUE;
  }

  if (last_fn == Script_FadeOut_b && !fading)
  {
    return TRUE;
  }

  if (last_fn == Script_LoadScene_b && !fading)
  {
    return TRUE;
  }

  if (last_fn == Script_ScenePopState_b)
  {
    return TRUE;
  }

  if (last_fn == Script_ScenePopAllState_b)
  {
    return TRUE;
  }

  if (last_fn == Script_LoadData_b && !fading)
  {
    return TRUE;
  }

  if (last_fn == Script_ActorSetEmote_b && !SceneIsEmoting())
  {
    return TRUE;
  }

  if (last_fn == Script_Text_b && UIIsClosed())
  {
    return TRUE;
  }

  if (last_fn == Script_Choice_b && UIIsClosed())
  {
    return TRUE;
  }

  if (last_fn == Script_TextMenu_b && UIIsClosed())
  {
    return TRUE;
  }

  if (last_fn == Script_OverlayMoveTo_b && UIAtDest())
  {
    return TRUE;
  }

  if (last_fn == Script_AwaitInput_b && SceneAwaitInputPressed())
  {
    return TRUE;
  }

  if (last_fn == Script_CameraMoveTo_b && SceneCameraAtDest())
  {
    camera_settings = camera_settings & ~CAMERA_TRANSITION_FLAG;
    return TRUE;
  }

  if (last_fn == Script_CameraLock_b && SceneCameraAtDest())
  {
    camera_settings = CAMERA_LOCK_FLAG;
    return TRUE;
  }

  if (last_fn == Script_TextWithAvatar_b && UIIsClosed())
  {
    return TRUE;
  }

  return FALSE;
}