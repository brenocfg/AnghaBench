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
 int get_num_expanded_data_rows () ; 
 TYPE_2__ gscroll ; 

__attribute__((used)) static void
page_up_module (void)
{
  int exp_size = get_num_expanded_data_rows ();
  int *scroll_ptr, *offset_ptr;

  scroll_ptr = &gscroll.module[gscroll.current].scroll;
  offset_ptr = &gscroll.module[gscroll.current].offset;

  if (!gscroll.expanded)
    return;
  /* decrease scroll and offset by exp_size */
  *scroll_ptr -= exp_size;
  if (*scroll_ptr < 0)
    *scroll_ptr = 0;

  if (*scroll_ptr < *offset_ptr)
    *offset_ptr -= exp_size;
  if (*offset_ptr <= 0)
    *offset_ptr = 0;
}