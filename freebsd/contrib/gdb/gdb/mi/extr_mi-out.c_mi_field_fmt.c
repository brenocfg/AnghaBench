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
typedef  int /*<<< orphan*/  va_list ;
struct ui_out {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  buffer; scalar_t__ suppress_output; } ;
typedef  TYPE_1__ mi_out_data ;
typedef  enum ui_align { ____Placeholder_ui_align } ui_align ;

/* Variables and functions */
 int /*<<< orphan*/  field_separator (struct ui_out*) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  fputs_unfiltered (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ui_out_data (struct ui_out*) ; 
 int /*<<< orphan*/  vfprintf_unfiltered (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void
mi_field_fmt (struct ui_out *uiout, int fldno,
	      int width, enum ui_align align,
	      const char *fldname,
	      const char *format,
	      va_list args)
{
  mi_out_data *data = ui_out_data (uiout);
  if (data->suppress_output)
    return;
  field_separator (uiout);
  if (fldname)
    fprintf_unfiltered (data->buffer, "%s=\"", fldname);
  else
    fputs_unfiltered ("\"", data->buffer);
  vfprintf_unfiltered (data->buffer, format, args);
  fputs_unfiltered ("\"", data->buffer);
}