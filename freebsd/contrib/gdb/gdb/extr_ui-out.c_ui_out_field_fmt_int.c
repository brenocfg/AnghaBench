#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ui_out_level {int dummy; } ;
struct ui_out {int dummy; } ;
typedef  enum ui_align { ____Placeholder_ui_align } ui_align ;

/* Variables and functions */
 struct ui_out_level* current_level (struct ui_out*) ; 
 int /*<<< orphan*/  uo_field_int (struct ui_out*,int,int,int,char const*,int) ; 
 int /*<<< orphan*/  verify_field (struct ui_out*,int*,int*,int*) ; 

void
ui_out_field_fmt_int (struct ui_out *uiout,
                      int input_width,
                      enum ui_align input_align,
		      const char *fldname,
		      int value)
{
  int fldno;
  int width;
  int align;
  struct ui_out_level *current = current_level (uiout);

  verify_field (uiout, &fldno, &width, &align);

  uo_field_int (uiout, fldno, input_width, input_align, fldname, value);
}