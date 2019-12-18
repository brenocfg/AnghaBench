#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dcols; } ;
struct TYPE_7__ {TYPE_2__* current; } ;
typedef  TYPE_1__ FORM ;
typedef  TYPE_2__ FIELD ;

/* Variables and functions */
 int /*<<< orphan*/  Address_Of_Current_Row_In_Buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  Adjust_Cursor_Position (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  Get_Start_Of_Data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Synchronize_Buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_CALLED (char*) ; 
 int /*<<< orphan*/  returnCode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
IFN_Beginning_Of_Line(FORM *form)
{
  FIELD *field = form->current;

  T((T_CALLED("IFN_Beginning_Of_Line(%p)"), (void *)form));
  Synchronize_Buffer(form);
  Adjust_Cursor_Position(form,
			 Get_Start_Of_Data(Address_Of_Current_Row_In_Buffer(form),
					   field->dcols));
  returnCode(E_OK);
}