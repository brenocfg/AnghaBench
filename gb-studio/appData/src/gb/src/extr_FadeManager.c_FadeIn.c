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
 int /*<<< orphan*/  ApplyPaletteChange (scalar_t__) ; 
 int /*<<< orphan*/  FADE_IN ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fade_direction ; 
 scalar_t__ fade_frame ; 
 int /*<<< orphan*/  fade_running ; 
 scalar_t__ fade_timer ; 

void FadeIn()
{
  fade_frame = 0;
  fade_direction = FADE_IN;
  fade_running = TRUE;
  fade_timer = 0;
  ApplyPaletteChange(fade_timer);
}