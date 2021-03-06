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
struct ui_out {int flags; } ;

/* Variables and functions */

int
ui_out_clear_flags (struct ui_out *uiout, int mask)
{
  int oldflags = uiout->flags;

  uiout->flags &= ~mask;

  return oldflags;
}