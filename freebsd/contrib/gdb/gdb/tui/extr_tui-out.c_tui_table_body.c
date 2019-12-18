#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ suppress_output; } ;
typedef  TYPE_1__ tui_out_data ;
struct ui_out {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tui_text (struct ui_out*,char*) ; 
 TYPE_1__* ui_out_data (struct ui_out*) ; 

void
tui_table_body (struct ui_out *uiout)
{
  tui_out_data *data = ui_out_data (uiout);
  if (data->suppress_output)
    return;
  /* first, close the table header line */
  tui_text (uiout, "\n");
}