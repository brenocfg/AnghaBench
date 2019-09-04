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
struct TYPE_8__ {TYPE_1__* module; scalar_t__ total_alloc; } ;
struct TYPE_7__ {size_t current; TYPE_2__* module; scalar_t__ dash; int /*<<< orphan*/  expanded; } ;
struct TYPE_6__ {int scroll; int offset; } ;
struct TYPE_5__ {int idx_data; } ;

/* Variables and functions */
 TYPE_4__* dash ; 
 int get_num_expanded_data_rows () ; 
 TYPE_3__ gscroll ; 
 scalar_t__ main_win_height ; 

__attribute__((used)) static void
scroll_to_last_line (void)
{
  int exp_size = get_num_expanded_data_rows ();
  int scrll = 0, offset = 0;

  if (!gscroll.expanded)
    gscroll.dash = dash->total_alloc - main_win_height;
  else {
    scrll = dash->module[gscroll.current].idx_data - 1;
    if (scrll >= exp_size && scrll >= offset + exp_size)
      offset = scrll < exp_size - 1 ? 0 : scrll - exp_size + 1;
    gscroll.module[gscroll.current].scroll = scrll;
    gscroll.module[gscroll.current].offset = offset;
  }
}