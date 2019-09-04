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
struct TYPE_4__ {size_t current; int /*<<< orphan*/  expanded; TYPE_1__* module; } ;
struct TYPE_3__ {int scroll; int offset; } ;

/* Variables and functions */
 TYPE_2__ gscroll ; 

__attribute__((used)) static void
scroll_up_expanded_module (void)
{
  int *scroll_ptr, *offset_ptr;

  scroll_ptr = &gscroll.module[gscroll.current].scroll;
  offset_ptr = &gscroll.module[gscroll.current].offset;

  if (!gscroll.expanded)
    return;
  if (*scroll_ptr <= 0)
    return;
  --(*scroll_ptr);
  if (*scroll_ptr < *offset_ptr)
    --(*offset_ptr);
}