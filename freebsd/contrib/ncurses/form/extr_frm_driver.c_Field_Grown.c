#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_15__ {int dcols; int drows; int cols; int maxgrow; int rows; int nrow; int nbuf; int /*<<< orphan*/ * buf; struct TYPE_15__* link; int /*<<< orphan*/  working; TYPE_1__* form; } ;
struct TYPE_14__ {int status; int /*<<< orphan*/  curcol; int /*<<< orphan*/  currow; int /*<<< orphan*/ * w; TYPE_2__* current; } ;
typedef  TYPE_1__ FORM ;
typedef  int /*<<< orphan*/  FIELD_CELL ;
typedef  TYPE_2__ FIELD ;

/* Variables and functions */
 int /*<<< orphan*/ * Address_Of_Nth_Buffer (TYPE_2__*,int) ; 
 int Buffer_Length (TYPE_2__*) ; 
 int /*<<< orphan*/  Buffer_To_Window (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ClrStatus (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ERR ; 
 int FALSE ; 
 scalar_t__ Growable (TYPE_2__*) ; 
 int Minimum (int,int) ; 
 int /*<<< orphan*/  SetStatus (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Set_Field_Window_Attributes (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int Single_Line_Field (TYPE_2__*) ; 
 int /*<<< orphan*/  Synchronize_Buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  T_CREATE (char*) ; 
 int /*<<< orphan*/  Total_Buffer_Size (TYPE_2__*) ; 
 int /*<<< orphan*/  _MAY_GROW ; 
 int _POSTED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  delwin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  myBLANK ; 
 int /*<<< orphan*/  myZEROS ; 
 int /*<<< orphan*/ * newpad (int,int) ; 
 int /*<<< orphan*/  untouchwin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  werase (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wresize (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool
Field_Grown(FIELD *field, int amount)
{
  bool result = FALSE;

  if (field && Growable(field))
    {
      bool single_line_field = Single_Line_Field(field);
      int old_buflen = Buffer_Length(field);
      int new_buflen;
      int old_dcols = field->dcols;
      int old_drows = field->drows;
      FIELD_CELL *oldbuf = field->buf;
      FIELD_CELL *newbuf;

      int growth;
      FORM *form = field->form;
      bool need_visual_update = ((form != (FORM *)0) &&
				 (form->status & _POSTED) &&
				 (form->current == field));

      if (need_visual_update)
	Synchronize_Buffer(form);

      if (single_line_field)
	{
	  growth = field->cols * amount;
	  if (field->maxgrow)
	    growth = Minimum(field->maxgrow - field->dcols, growth);
	  field->dcols += growth;
	  if (field->dcols == field->maxgrow)
	    ClrStatus(field, _MAY_GROW);
	}
      else
	{
	  growth = (field->rows + field->nrow) * amount;
	  if (field->maxgrow)
	    growth = Minimum(field->maxgrow - field->drows, growth);
	  field->drows += growth;
	  if (field->drows == field->maxgrow)
	    ClrStatus(field, _MAY_GROW);
	}
      /* drows, dcols changed, so we get really the new buffer length */
      new_buflen = Buffer_Length(field);
      newbuf = (FIELD_CELL *)malloc(Total_Buffer_Size(field));
      if (!newbuf)
	{
	  /* restore to previous state */
	  field->dcols = old_dcols;
	  field->drows = old_drows;
	  if ((single_line_field && (field->dcols != field->maxgrow)) ||
	      (!single_line_field && (field->drows != field->maxgrow)))
	    SetStatus(field, _MAY_GROW);
	}
      else
	{
	  /* Copy all the buffers.  This is the reason why we can't just use
	   * realloc().
	   */
	  int i, j;
	  FIELD_CELL *old_bp;
	  FIELD_CELL *new_bp;

	  result = TRUE;	/* allow sharing of recovery on failure */

	  T((T_CREATE("fieldcell %p"), (void *)newbuf));
	  field->buf = newbuf;
	  for (i = 0; i <= field->nbuf; i++)
	    {
	      new_bp = Address_Of_Nth_Buffer(field, i);
	      old_bp = oldbuf + i * (1 + old_buflen);
	      for (j = 0; j < old_buflen; ++j)
		new_bp[j] = old_bp[j];
	      while (j < new_buflen)
		new_bp[j++] = myBLANK;
	      new_bp[new_buflen] = myZEROS;
	    }

#if USE_WIDEC_SUPPORT && NCURSES_EXT_FUNCS
	  if (wresize(field->working, 1, Buffer_Length(field) + 1) == ERR)
	    result = FALSE;
#endif

	  if (need_visual_update && result)
	    {
	      WINDOW *new_window = newpad(field->drows, field->dcols);

	      if (new_window != 0)
		{
		  assert(form != (FORM *)0);
		  if (form->w)
		    delwin(form->w);
		  form->w = new_window;
		  Set_Field_Window_Attributes(field, form->w);
		  werase(form->w);
		  Buffer_To_Window(field, form->w);
		  untouchwin(form->w);
		  wmove(form->w, form->currow, form->curcol);
		}
	      else
		result = FALSE;
	    }

	  if (result)
	    {
	      free(oldbuf);
	      /* reflect changes in linked fields */
	      if (field != field->link)
		{
		  FIELD *linked_field;

		  for (linked_field = field->link;
		       linked_field != field;
		       linked_field = linked_field->link)
		    {
		      linked_field->buf = field->buf;
		      linked_field->drows = field->drows;
		      linked_field->dcols = field->dcols;
		    }
		}
	    }
	  else
	    {
	      /* restore old state */
	      field->dcols = old_dcols;
	      field->drows = old_drows;
	      field->buf = oldbuf;
	      if ((single_line_field &&
		   (field->dcols != field->maxgrow)) ||
		  (!single_line_field &&
		   (field->drows != field->maxgrow)))
		SetStatus(field, _MAY_GROW);
	      free(newbuf);
	    }
	}
    }
  return (result);
}