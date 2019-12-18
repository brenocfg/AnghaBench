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
struct TYPE_14__ {int drows; int dcols; scalar_t__ opts; } ;
struct TYPE_13__ {int currow; int curcol; int /*<<< orphan*/  w; TYPE_2__* current; } ;
typedef  TYPE_1__ FORM ;
typedef  int /*<<< orphan*/  FIELD_CELL ;
typedef  TYPE_2__ FIELD ;

/* Variables and functions */
 int /*<<< orphan*/ * Address_Of_Current_Row_In_Buffer (TYPE_1__*) ; 
 int /*<<< orphan*/ * After_Last_Whitespace_Character (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DeleteChar (TYPE_1__*) ; 
 int E_OK ; 
 int E_REQUEST_DENIED ; 
 int E_SYSTEM_ERROR ; 
 int /*<<< orphan*/  Field_Grown (TYPE_2__*,int) ; 
 scalar_t__ Growable (TYPE_2__*) ; 
 int Insert_String (TYPE_1__*,int,int /*<<< orphan*/ *,int) ; 
 unsigned int O_WRAP ; 
 int /*<<< orphan*/  Single_Line_Field (TYPE_2__*) ; 
 scalar_t__ There_Is_No_Room_For_A_Char_In_Line (TYPE_1__*) ; 
 int /*<<< orphan*/  Window_To_Buffer (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  wclrtoeol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
Wrapping_Not_Necessary_Or_Wrapping_Ok(FORM *form)
{
  FIELD *field = form->current;
  int result = E_REQUEST_DENIED;
  bool Last_Row = ((field->drows - 1) == form->currow);

  if (((unsigned)field->opts & O_WRAP) &&	/* wrapping wanted     */
      (!Single_Line_Field(field)) &&	/* must be multi-line  */
      (There_Is_No_Room_For_A_Char_In_Line(form)) &&	/* line is full        */
      (!Last_Row || Growable(field)))	/* there are more lines */
    {
      FIELD_CELL *bp;
      FIELD_CELL *split;
      int chars_to_be_wrapped;
      int chars_to_remain_on_line;

      if (Last_Row)
	{
	  /* the above logic already ensures, that in this case the field
	     is growable */
	  if (!Field_Grown(field, 1))
	    return E_SYSTEM_ERROR;
	}
      bp = Address_Of_Current_Row_In_Buffer(form);
      Window_To_Buffer(form, field);
      split = After_Last_Whitespace_Character(bp, field->dcols);
      /* split points to the first character of the sequence to be brought
         on the next line */
      chars_to_remain_on_line = (int)(split - bp);
      chars_to_be_wrapped = field->dcols - chars_to_remain_on_line;
      if (chars_to_remain_on_line > 0)
	{
	  if ((result = Insert_String(form, form->currow + 1, split,
				      chars_to_be_wrapped)) == E_OK)
	    {
	      wmove(form->w, form->currow, chars_to_remain_on_line);
	      wclrtoeol(form->w);
	      if (form->curcol >= chars_to_remain_on_line)
		{
		  form->currow++;
		  form->curcol -= chars_to_remain_on_line;
		}
	      return E_OK;
	    }
	}
      else
	return E_OK;
      if (result != E_OK)
	{
	  DeleteChar(form);
	  Window_To_Buffer(form, field);
	  result = E_REQUEST_DENIED;
	}
    }
  else
    result = E_OK;		/* wrapping was not necessary */
  return (result);
}