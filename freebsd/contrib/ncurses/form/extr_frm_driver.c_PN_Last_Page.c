#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ maxpage; } ;
typedef  TYPE_1__ FORM ;
typedef  int /*<<< orphan*/  FIELD ;

/* Variables and functions */
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_CALLED (char*) ; 
 int /*<<< orphan*/  _nc_Set_Form_Page (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  returnCode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
PN_Last_Page(FORM *form)
{
  T((T_CALLED("PN_Last_Page(%p)"), (void *)form));
  returnCode(_nc_Set_Form_Page(form, form->maxpage - 1, (FIELD *)0));
}