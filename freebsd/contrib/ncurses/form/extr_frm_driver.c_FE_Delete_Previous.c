#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int cols; int /*<<< orphan*/  dcols; } ;
struct TYPE_9__ {scalar_t__ curcol; int currow; int status; int /*<<< orphan*/  w; TYPE_2__* current; } ;
typedef  TYPE_1__ FORM ;
typedef  int /*<<< orphan*/  FIELD_CELL ;
typedef  TYPE_2__ FIELD ;

/* Variables and functions */
 int /*<<< orphan*/ * Address_Of_Row_In_Buffer (TYPE_2__*,int) ; 
 int /*<<< orphan*/  Adjust_Cursor_Position (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * After_End_Of_Data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteChar (TYPE_1__*) ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  E_REQUEST_DENIED ; 
 scalar_t__ First_Position_In_Current_Field (TYPE_1__*) ; 
 int /*<<< orphan*/  Synchronize_Buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_CALLED (char*) ; 
 int _OVLMODE ; 
 int /*<<< orphan*/  myADDNSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  returnCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdeleteln (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static int
FE_Delete_Previous(FORM *form)
{
  FIELD *field = form->current;

  T((T_CALLED("FE_Delete_Previous(%p)"), (void *)form));
  if (First_Position_In_Current_Field(form))
    returnCode(E_REQUEST_DENIED);

  if ((--(form->curcol)) < 0)
    {
      FIELD_CELL *this_line, *prev_line, *prev_end, *this_end;
      int this_row = form->currow;

      form->curcol++;
      if (form->status & _OVLMODE)
	returnCode(E_REQUEST_DENIED);

      prev_line = Address_Of_Row_In_Buffer(field, (form->currow - 1));
      this_line = Address_Of_Row_In_Buffer(field, (form->currow));
      Synchronize_Buffer(form);
      prev_end = After_End_Of_Data(prev_line, field->dcols);
      this_end = After_End_Of_Data(this_line, field->dcols);
      if ((int)(this_end - this_line) >
	  (field->cols - (int)(prev_end - prev_line)))
	returnCode(E_REQUEST_DENIED);
      wmove(form->w, form->currow, form->curcol);
      wdeleteln(form->w);
      Adjust_Cursor_Position(form, prev_end);
      /*
       * If we did not really move to the previous line, help the user a
       * little.  It is however a little inconsistent.  Normally, when
       * backspacing around the point where text wraps to a new line in a
       * multi-line form, we absorb one keystroke for the wrapping point.  That
       * is consistent with SVr4 forms.  However, SVr4 does not allow typing
       * into the last column of the field, and requires the user to enter a
       * newline to move to the next line.  Therefore it can consistently eat
       * that keystroke.  Since ncurses allows the last column, it wraps
       * automatically (given the proper options).  But we cannot eat the
       * keystroke to back over the wrapping point, since that would put the
       * cursor past the end of the form field.  In this case, just delete the
       * character at the end of the field.
       */
      if (form->currow == this_row && this_row > 0)
	{
	  form->currow -= 1;
	  form->curcol = field->dcols - 1;
	  DeleteChar(form);
	}
      else
	{
	  wmove(form->w, form->currow, form->curcol);
	  myADDNSTR(form->w, this_line, (int)(this_end - this_line));
	}
    }
  else
    {
      DeleteChar(form);
    }
  returnCode(E_OK);
}