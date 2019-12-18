#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int drows; scalar_t__ dcols; } ;
struct TYPE_11__ {int currow; int status; int /*<<< orphan*/  w; scalar_t__ curcol; scalar_t__ opts; TYPE_2__* current; } ;
typedef  TYPE_1__ FORM ;
typedef  int /*<<< orphan*/  FIELD_CELL ;
typedef  TYPE_2__ FIELD ;

/* Variables and functions */
 int /*<<< orphan*/ * Address_Of_Current_Position_In_Buffer (TYPE_1__*) ; 
 int /*<<< orphan*/ * After_End_Of_Data (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  E_REQUEST_DENIED ; 
 int /*<<< orphan*/  E_SYSTEM_ERROR ; 
 int /*<<< orphan*/  FN_Next_Field ; 
 int /*<<< orphan*/  Field_Grown (TYPE_2__*,int) ; 
 scalar_t__ Growable (TYPE_2__*) ; 
 int /*<<< orphan*/  Inter_Field_Navigation (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ Is_There_Room_For_A_Line (TYPE_1__*) ; 
 unsigned int O_NL_OVERLOAD ; 
 int /*<<< orphan*/  SetStatus (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Single_Line_Field (TYPE_2__*) ; 
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_CALLED (char*) ; 
 int _OVLMODE ; 
 int /*<<< orphan*/  _WINDOW_MODIFIED ; 
 int /*<<< orphan*/  myADDNSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  returnCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wclrtoeol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  winsertln (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static int
FE_New_Line(FORM *form)
{
  FIELD *field = form->current;
  FIELD_CELL *bp, *t;
  bool Last_Row = ((field->drows - 1) == form->currow);

  T((T_CALLED("FE_New_Line(%p)"), (void *)form));
  if (form->status & _OVLMODE)
    {
      if (Last_Row &&
	  (!(Growable(field) && !Single_Line_Field(field))))
	{
	  if (!((unsigned)form->opts & O_NL_OVERLOAD))
	    returnCode(E_REQUEST_DENIED);
	  wmove(form->w, form->currow, form->curcol);
	  wclrtoeol(form->w);
	  /* we have to set this here, although it is also
	     handled in the generic routine. The reason is,
	     that FN_Next_Field may fail, but the form is
	     definitively changed */
	  SetStatus(form, _WINDOW_MODIFIED);
	  returnCode(Inter_Field_Navigation(FN_Next_Field, form));
	}
      else
	{
	  if (Last_Row && !Field_Grown(field, 1))
	    {
	      /* N.B.: due to the logic in the 'if', LastRow==TRUE
	         means here that the field is growable and not
	         a single-line field */
	      returnCode(E_SYSTEM_ERROR);
	    }
	  wmove(form->w, form->currow, form->curcol);
	  wclrtoeol(form->w);
	  form->currow++;
	  form->curcol = 0;
	  SetStatus(form, _WINDOW_MODIFIED);
	  returnCode(E_OK);
	}
    }
  else
    {
      /* Insert Mode */
      if (Last_Row &&
	  !(Growable(field) && !Single_Line_Field(field)))
	{
	  if (!((unsigned)form->opts & O_NL_OVERLOAD))
	    returnCode(E_REQUEST_DENIED);
	  returnCode(Inter_Field_Navigation(FN_Next_Field, form));
	}
      else
	{
	  bool May_Do_It = !Last_Row && Is_There_Room_For_A_Line(form);

	  if (!(May_Do_It || Growable(field)))
	    returnCode(E_REQUEST_DENIED);
	  if (!May_Do_It && !Field_Grown(field, 1))
	    returnCode(E_SYSTEM_ERROR);

	  bp = Address_Of_Current_Position_In_Buffer(form);
	  t = After_End_Of_Data(bp, field->dcols - form->curcol);
	  wmove(form->w, form->currow, form->curcol);
	  wclrtoeol(form->w);
	  form->currow++;
	  form->curcol = 0;
	  wmove(form->w, form->currow, form->curcol);
	  winsertln(form->w);
	  myADDNSTR(form->w, bp, (int)(t - bp));
	  SetStatus(form, _WINDOW_MODIFIED);
	  returnCode(E_OK);
	}
    }
}