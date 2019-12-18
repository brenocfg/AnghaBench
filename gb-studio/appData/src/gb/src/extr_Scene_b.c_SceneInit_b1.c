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
 int /*<<< orphan*/  DISPLAY_OFF ; 
 void* FALSE ; 
 int /*<<< orphan*/  MAXWNDPOSX ; 
 int /*<<< orphan*/  MAXWNDPOSY ; 
 scalar_t__ SCX_REG ; 
 scalar_t__ SCY_REG ; 
 int /*<<< orphan*/  SpritesReset () ; 
 int /*<<< orphan*/  UIInit () ; 
 int /*<<< orphan*/  WX_REG ; 
 int /*<<< orphan*/  WY_REG ; 
 void* scene_input_ready ; 
 void* scene_loaded ; 

void SceneInit_b1()
{
  DISPLAY_OFF;

  scene_loaded = FALSE;
  scene_input_ready = FALSE;

  SpritesReset();
  UIInit();

  SCX_REG = 0;
  SCY_REG = 0;
  WX_REG = MAXWNDPOSX;
  WY_REG = MAXWNDPOSY;

  // Load scene
}