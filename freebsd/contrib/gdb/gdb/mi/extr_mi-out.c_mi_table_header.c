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
typedef  enum ui_align { ____Placeholder_ui_align } ui_align ;

/* Variables and functions */
 int /*<<< orphan*/  mi_close (struct ui_out*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mi_field_int (struct ui_out*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mi_field_string (struct ui_out*,int /*<<< orphan*/ ,int,int,char*,char const*) ; 
 int /*<<< orphan*/  mi_open (struct ui_out*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ui_out_data (struct ui_out*) ; 
 int /*<<< orphan*/  ui_out_type_tuple ; 

void
mi_table_header (struct ui_out *uiout, int width, enum ui_align alignment,
		 const char *col_name,
		 const char *colhdr)
{
  mi_out_data *data = ui_out_data (uiout);
  if (data->suppress_output)
    return;
  mi_open (uiout, NULL, ui_out_type_tuple);
  mi_field_int (uiout, 0, 0, 0, "width", width);
  mi_field_int (uiout, 0, 0, 0, "alignment", alignment);
  mi_field_string (uiout, 0, 0, 0, "col_name", col_name);
  mi_field_string (uiout, 0, width, alignment, "colhdr", colhdr);
  mi_close (uiout, ui_out_type_tuple);
}