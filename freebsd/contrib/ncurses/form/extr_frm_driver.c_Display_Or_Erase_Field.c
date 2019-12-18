#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_8__ {scalar_t__ opts; int /*<<< orphan*/  fcol; int /*<<< orphan*/  frow; int /*<<< orphan*/  cols; int /*<<< orphan*/  rows; int /*<<< orphan*/  form; } ;
typedef  TYPE_1__ FIELD ;

/* Variables and functions */
 int /*<<< orphan*/  Buffer_To_Window (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ClrStatus (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int E_OK ; 
 int E_SYSTEM_ERROR ; 
 int /*<<< orphan*/ * Get_Form_Window (int /*<<< orphan*/ ) ; 
 scalar_t__ Justification_Allowed (TYPE_1__*) ; 
 unsigned int O_PUBLIC ; 
 unsigned int O_VISIBLE ; 
 int /*<<< orphan*/  Perform_Justification (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Set_Field_Window_Attributes (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ WINDOW_ATTRS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _NEWTOP ; 
 int /*<<< orphan*/  delwin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * derwin (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wattrset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  werase (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wsyncup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
Display_Or_Erase_Field(FIELD *field, bool bEraseFlag)
{
  WINDOW *win;
  WINDOW *fwin;

  if (!field)
    return E_SYSTEM_ERROR;

  fwin = Get_Form_Window(field->form);
  win = derwin(fwin,
	       field->rows, field->cols, field->frow, field->fcol);

  if (!win)
    return E_SYSTEM_ERROR;
  else
    {
      if ((unsigned)field->opts & O_VISIBLE)
	{
	  Set_Field_Window_Attributes(field, win);
	}
      else
	{
	  (void)wattrset(win, (int)WINDOW_ATTRS(fwin));
	}
      werase(win);
    }

  if (!bEraseFlag)
    {
      if ((unsigned)field->opts & O_PUBLIC)
	{
	  if (Justification_Allowed(field))
	    Perform_Justification(field, win);
	  else
	    Buffer_To_Window(field, win);
	}
      ClrStatus(field, _NEWTOP);
    }
  wsyncup(win);
  delwin(win);
  return E_OK;
}