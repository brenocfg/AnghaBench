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
struct ui_out {int dummy; } ;
struct TYPE_3__ {scalar_t__ suppress_output; } ;
typedef  TYPE_1__ mi_out_data ;

/* Variables and functions */
 int /*<<< orphan*/  mi_close (struct ui_out*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mi_open (struct ui_out*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ui_out_data (struct ui_out*) ; 
 int /*<<< orphan*/  ui_out_type_list ; 

void
mi_table_body (struct ui_out *uiout)
{
  mi_out_data *data = ui_out_data (uiout);
  if (data->suppress_output)
    return;
  /* close the table header line if there were any headers */
  mi_close (uiout, ui_out_type_list);
  mi_open (uiout, "body", ui_out_type_list);
}