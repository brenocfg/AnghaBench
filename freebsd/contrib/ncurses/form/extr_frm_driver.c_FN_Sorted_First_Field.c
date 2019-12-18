#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t curpage; TYPE_1__* page; int /*<<< orphan*/ * field; } ;
struct TYPE_5__ {size_t smax; } ;
typedef  TYPE_2__ FORM ;

/* Variables and functions */
 int /*<<< orphan*/  Sorted_Next_Field (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_CALLED (char*) ; 
 int /*<<< orphan*/  _nc_Set_Current_Field (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  returnCode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
FN_Sorted_First_Field(FORM *form)
{
  T((T_CALLED("FN_Sorted_First_Field(%p)"), (void *)form));
  returnCode(_nc_Set_Current_Field(form,
				   Sorted_Next_Field(form->field[form->page[form->curpage].smax])));
}