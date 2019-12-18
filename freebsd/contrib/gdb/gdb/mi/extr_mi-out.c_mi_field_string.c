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
struct TYPE_3__ {int /*<<< orphan*/  buffer; scalar_t__ suppress_output; } ;
typedef  TYPE_1__ mi_out_data ;
typedef  enum ui_align { ____Placeholder_ui_align } ui_align ;

/* Variables and functions */
 int /*<<< orphan*/  field_separator (struct ui_out*) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputstr_unfiltered (char const*,char,int /*<<< orphan*/ ) ; 
 TYPE_1__* ui_out_data (struct ui_out*) ; 

void
mi_field_string (struct ui_out *uiout,
		 int fldno,
		 int width,
		 enum ui_align align,
		 const char *fldname,
		 const char *string)
{
  mi_out_data *data = ui_out_data (uiout);
  if (data->suppress_output)
    return;
  field_separator (uiout);
  if (fldname)
    fprintf_unfiltered (data->buffer, "%s=", fldname);
  fprintf_unfiltered (data->buffer, "\"");
  if (string)
    fputstr_unfiltered (string, '"', data->buffer);
  fprintf_unfiltered (data->buffer, "\"");
}