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
 int /*<<< orphan*/  ApplyPaletteChange (int) ; 
 int /*<<< orphan*/  FADE_OUT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fade_direction ; 
 scalar_t__ fade_frame ; 
 int /*<<< orphan*/  fade_running ; 
 int fade_timer ; 

void FadeOut()
{
  fade_frame = 0;
  fade_direction = FADE_OUT;
  fade_running = TRUE;
  fade_timer = 5;
  ApplyPaletteChange(fade_timer);
}