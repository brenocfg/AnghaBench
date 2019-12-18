#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t current; TYPE_1__* module; scalar_t__ dash; int /*<<< orphan*/  expanded; } ;
struct TYPE_3__ {scalar_t__ offset; scalar_t__ scroll; } ;

/* Variables and functions */
 TYPE_2__ gscroll ; 

__attribute__((used)) static void
scroll_to_first_line (void)
{
  if (!gscroll.expanded)
    gscroll.dash = 0;
  else {
    gscroll.module[gscroll.current].scroll = 0;
    gscroll.module[gscroll.current].offset = 0;
  }
}