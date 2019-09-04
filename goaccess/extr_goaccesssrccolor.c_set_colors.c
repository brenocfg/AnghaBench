#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ color_idx; int /*<<< orphan*/  colors; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_default_colors () ; 
 TYPE_1__ conf ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  parse_colors (int /*<<< orphan*/ ,scalar_t__) ; 

void
set_colors (int force)
{
  errno = 0;
  if (conf.color_idx > 0 && !force)
    parse_colors (conf.colors, conf.color_idx);
  else
    add_default_colors ();
}