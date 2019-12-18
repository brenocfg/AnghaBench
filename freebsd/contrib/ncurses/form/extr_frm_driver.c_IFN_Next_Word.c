#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * buf; } ;
struct TYPE_8__ {TYPE_2__* current; } ;
typedef  TYPE_1__ FORM ;
typedef  int /*<<< orphan*/  FIELD_CELL ;
typedef  TYPE_2__ FIELD ;

/* Variables and functions */
 int /*<<< orphan*/ * Address_Of_Current_Position_In_Buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  Adjust_Cursor_Position (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ Buffer_Length (TYPE_2__*) ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  E_REQUEST_DENIED ; 
 int /*<<< orphan*/ * Get_First_Whitespace_Character (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * Get_Start_Of_Data (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  Synchronize_Buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_CALLED (char*) ; 
 int /*<<< orphan*/  returnCode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
IFN_Next_Word(FORM *form)
{
  FIELD *field = form->current;
  FIELD_CELL *bp = Address_Of_Current_Position_In_Buffer(form);
  FIELD_CELL *s;
  FIELD_CELL *t;

  T((T_CALLED("IFN_Next_Word(%p)"), (void *)form));

  /* We really need access to the data, so we have to synchronize */
  Synchronize_Buffer(form);

  /* Go to the first whitespace after the current position (including
     current position). This is then the starting point to look for the
     next non-blank data */
  s = Get_First_Whitespace_Character(bp, Buffer_Length(field) -
				     (int)(bp - field->buf));

  /* Find the start of the next word */
  t = Get_Start_Of_Data(s, Buffer_Length(field) -
			(int)(s - field->buf));
#if !FRIENDLY_PREV_NEXT_WORD
  if (s == t)
    returnCode(E_REQUEST_DENIED);
  else
#endif
    {
      Adjust_Cursor_Position(form, t);
      returnCode(E_OK);
    }
}