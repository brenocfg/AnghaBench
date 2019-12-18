#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ui_out {TYPE_1__* impl; } ;
typedef  enum ui_align { ____Placeholder_ui_align } ui_align ;
struct TYPE_2__ {int /*<<< orphan*/  (* field_string ) (struct ui_out*,int,int,int,char const*,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ui_out*,int,int,int,char const*,char const*) ; 

void
uo_field_string (struct ui_out *uiout, int fldno, int width,
		 enum ui_align align,
		 const char *fldname,
		 const char *string)
{
  if (!uiout->impl->field_string)
    return;
  uiout->impl->field_string (uiout, fldno, width, align, fldname, string);
}