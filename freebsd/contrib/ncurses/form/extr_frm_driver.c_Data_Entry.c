#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  chtype ;
struct TYPE_14__ {int drows; int dcols; scalar_t__ opts; } ;
struct TYPE_13__ {int status; int currow; int curcol; int /*<<< orphan*/  w; TYPE_2__* current; } ;
typedef  TYPE_1__ FORM ;
typedef  TYPE_2__ FIELD ;

/* Variables and functions */
 int E_OK ; 
 int E_REQUEST_DENIED ; 
 int E_SYSTEM_ERROR ; 
 int /*<<< orphan*/  FN_Next_Field ; 
 int /*<<< orphan*/  Field_Grown (TYPE_2__*,int) ; 
 scalar_t__ First_Position_In_Current_Field (TYPE_1__*) ; 
 scalar_t__ Growable (TYPE_2__*) ; 
 int /*<<< orphan*/  IFN_Next_Character (TYPE_1__*) ; 
 int Inter_Field_Navigation (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int Is_There_Room_For_A_Char_In_Line (TYPE_1__*) ; 
 unsigned int O_ACTIVE ; 
 unsigned int O_AUTOSKIP ; 
 unsigned int O_BLANK ; 
 unsigned int O_EDIT ; 
 int /*<<< orphan*/  RETURN (int) ; 
 int /*<<< orphan*/  SetStatus (TYPE_1__*,int) ; 
 scalar_t__ Single_Line_Field (TYPE_2__*) ; 
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_CALLED (char*) ; 
 scalar_t__ WINDOW_EXT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int Wrapping_Not_Necessary_Or_Wrapping_Ok (TYPE_1__*) ; 
 int _FCHECK_REQUIRED ; 
 int _OVLMODE ; 
 int _WINDOW_MODIFIED ; 
 int /*<<< orphan*/  _tracechtype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addch_used ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  werase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  winsch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
Data_Entry(FORM *form, int c)
{
  FIELD *field = form->current;
  int result = E_REQUEST_DENIED;

  T((T_CALLED("Data_Entry(%p,%s)"), (void *)form, _tracechtype((chtype)c)));
  if (((unsigned)field->opts & O_EDIT)
#if FIX_FORM_INACTIVE_BUG
      && ((unsigned)field->opts & O_ACTIVE)
#endif
    )
    {
      if (((unsigned)field->opts & O_BLANK) &&
	  First_Position_In_Current_Field(form) &&
	  !(form->status & _FCHECK_REQUIRED) &&
	  !(form->status & _WINDOW_MODIFIED))
	werase(form->w);

      if (form->status & _OVLMODE)
	{
	  waddch(form->w, (chtype)c);
	}
      else
	/* no _OVLMODE */
	{
	  bool There_Is_Room = Is_There_Room_For_A_Char_In_Line(form);

	  if (!(There_Is_Room ||
		((Single_Line_Field(field) && Growable(field)))))
	    RETURN(E_REQUEST_DENIED);

	  if (!There_Is_Room && !Field_Grown(field, 1))
	    RETURN(E_SYSTEM_ERROR);

	  winsch(form->w, (chtype)c);
	}

      if ((result = Wrapping_Not_Necessary_Or_Wrapping_Ok(form)) == E_OK)
	{
	  bool End_Of_Field = (((field->drows - 1) == form->currow) &&
			       ((field->dcols - 1) == form->curcol));

	  SetStatus(form, _WINDOW_MODIFIED);
	  if (End_Of_Field && !Growable(field) && ((unsigned)field->opts & O_AUTOSKIP))
	    result = Inter_Field_Navigation(FN_Next_Field, form);
	  else
	    {
	      if (End_Of_Field && Growable(field) && !Field_Grown(field, 1))
		result = E_SYSTEM_ERROR;
	      else
		{
#if USE_WIDEC_SUPPORT
		  /*
		   * We have just added a byte to the form field.  It may have
		   * been part of a multibyte character.  If it was, the
		   * addch_used field is nonzero and we should not try to move
		   * to a new column.
		   */
		  if (WINDOW_EXT(form->w, addch_used) == 0)
		    IFN_Next_Character(form);
#else
		  IFN_Next_Character(form);
#endif
		  result = E_OK;
		}
	    }
	}
    }
  RETURN(result);
}