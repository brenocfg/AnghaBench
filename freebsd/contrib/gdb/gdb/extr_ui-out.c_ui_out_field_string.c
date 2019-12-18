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
struct ui_out {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  uo_field_string (struct ui_out*,int,int,int,char const*,char const*) ; 
 int /*<<< orphan*/  verify_field (struct ui_out*,int*,int*,int*) ; 

void
ui_out_field_string (struct ui_out *uiout,
		     const char *fldname,
		     const char *string)
{
  int fldno;
  int width;
  int align;

  verify_field (uiout, &fldno, &width, &align);

  uo_field_string (uiout, fldno, width, align, fldname, string);
}