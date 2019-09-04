#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* module; } ;
struct TYPE_7__ {size_t current; int /*<<< orphan*/  expanded; TYPE_1__* module; } ;
struct TYPE_6__ {int idx_data; } ;
struct TYPE_5__ {int scroll; int offset; } ;

/* Variables and functions */
 TYPE_4__* dash ; 
 int get_num_expanded_data_rows () ; 
 TYPE_3__ gscroll ; 

__attribute__((used)) static void
page_down_module (void)
{
  int exp_size = get_num_expanded_data_rows ();
  int *scroll_ptr, *offset_ptr;

  scroll_ptr = &gscroll.module[gscroll.current].scroll;
  offset_ptr = &gscroll.module[gscroll.current].offset;

  if (!gscroll.expanded)
    return;

  *scroll_ptr += exp_size;
  if (*scroll_ptr >= dash->module[gscroll.current].idx_data - 1)
    *scroll_ptr = dash->module[gscroll.current].idx_data - 1;
  if (*scroll_ptr >= exp_size && *scroll_ptr >= *offset_ptr + exp_size)
    *offset_ptr += exp_size;
  if (*offset_ptr + exp_size >= dash->module[gscroll.current].idx_data - 1)
    *offset_ptr = dash->module[gscroll.current].idx_data - exp_size;
  if (*scroll_ptr < exp_size - 1)
    *offset_ptr = 0;
}