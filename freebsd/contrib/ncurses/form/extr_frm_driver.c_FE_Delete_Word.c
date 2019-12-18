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
struct TYPE_8__ {int dcols; } ;
struct TYPE_7__ {int curcol; int /*<<< orphan*/  w; int /*<<< orphan*/  currow; TYPE_2__* current; } ;
typedef  TYPE_1__ FORM ;
typedef  int /*<<< orphan*/  FIELD_CELL ;
typedef  TYPE_2__ FIELD ;

/* Variables and functions */
 int /*<<< orphan*/ * Address_Of_Current_Row_In_Buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  Adjust_Cursor_Position (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * After_End_Of_Data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  After_Last_Whitespace_Character (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  E_REQUEST_DENIED ; 
 int /*<<< orphan*/ * Get_First_Whitespace_Character (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * Get_Start_Of_Data (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ISBLANK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Synchronize_Buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_CALLED (char*) ; 
 int /*<<< orphan*/  myADDNSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  returnCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wclrtoeol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
FE_Delete_Word(FORM *form)
{
  FIELD *field = form->current;
  FIELD_CELL *bp = Address_Of_Current_Row_In_Buffer(form);
  FIELD_CELL *ep = bp + field->dcols;
  FIELD_CELL *cp = bp + form->curcol;
  FIELD_CELL *s;

  T((T_CALLED("FE_Delete_Word(%p)"), (void *)form));
  Synchronize_Buffer(form);
  if (ISBLANK(*cp))
    returnCode(E_REQUEST_DENIED);	/* not in word */

  /* move cursor to begin of word and erase to end of screen-line */
  Adjust_Cursor_Position(form,
			 After_Last_Whitespace_Character(bp, form->curcol));
  wmove(form->w, form->currow, form->curcol);
  wclrtoeol(form->w);

  /* skip over word in buffer */
  s = Get_First_Whitespace_Character(cp, (int)(ep - cp));
  /* to begin of next word    */
  s = Get_Start_Of_Data(s, (int)(ep - s));
  if ((s != cp) && !ISBLANK(*s))
    {
      /* copy remaining line to window */
      myADDNSTR(form->w, s, (int)(s - After_End_Of_Data(s, (int)(ep - s))));
    }
  returnCode(E_OK);
}