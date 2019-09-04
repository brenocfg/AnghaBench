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
 int /*<<< orphan*/  set_colors (int) ; 
 int /*<<< orphan*/  set_normal_color () ; 
 int /*<<< orphan*/  use_default_colors () ; 

void
init_colors (int force)
{
  /* use default foreground/background colors */
  use_default_colors ();
  /* first set a default normal color */
  set_normal_color ();
  /* then parse custom colors and initialize them */
  set_colors (force);
}