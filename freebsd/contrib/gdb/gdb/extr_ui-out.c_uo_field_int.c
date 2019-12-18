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
struct TYPE_2__ {int /*<<< orphan*/  (* field_int ) (struct ui_out*,int,int,int,char const*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ui_out*,int,int,int,char const*,int) ; 

void
uo_field_int (struct ui_out *uiout, int fldno, int width, enum ui_align align,
	      const char *fldname,
	      int value)
{
  if (!uiout->impl->field_int)
    return;
  uiout->impl->field_int (uiout, fldno, width, align, fldname, value);
}