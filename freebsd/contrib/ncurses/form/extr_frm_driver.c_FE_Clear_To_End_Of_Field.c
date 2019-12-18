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
struct TYPE_3__ {int /*<<< orphan*/  w; int /*<<< orphan*/  curcol; int /*<<< orphan*/  currow; } ;
typedef  TYPE_1__ FORM ;

/* Variables and functions */
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_CALLED (char*) ; 
 int /*<<< orphan*/  returnCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wclrtobot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
FE_Clear_To_End_Of_Field(FORM *form)
{
  T((T_CALLED("FE_Clear_To_End_Of_Field(%p)"), (void *)form));
  wmove(form->w, form->currow, form->curcol);
  wclrtobot(form->w);
  returnCode(E_OK);
}