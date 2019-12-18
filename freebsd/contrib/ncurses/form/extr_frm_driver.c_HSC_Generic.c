#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int dcols; int cols; } ;
struct TYPE_4__ {int begincol; int curcol; TYPE_2__* current; } ;
typedef  TYPE_1__ FORM ;
typedef  TYPE_2__ FIELD ;

/* Variables and functions */
 int E_OK ; 
 int E_REQUEST_DENIED ; 

__attribute__((used)) static int
HSC_Generic(FORM *form, int ncolumns)
{
  FIELD *field = form->current;
  int res = E_REQUEST_DENIED;
  int cols_to_go = (ncolumns > 0 ? ncolumns : -ncolumns);

  if (ncolumns > 0)
    {
      if ((cols_to_go + form->begincol) > (field->dcols - field->cols))
	cols_to_go = field->dcols - field->cols - form->begincol;

      if (cols_to_go > 0)
	{
	  form->curcol += cols_to_go;
	  form->begincol += cols_to_go;
	  res = E_OK;
	}
    }
  else
    {
      if (cols_to_go > form->begincol)
	cols_to_go = form->begincol;

      if (cols_to_go > 0)
	{
	  form->curcol -= cols_to_go;
	  form->begincol -= cols_to_go;
	  res = E_OK;
	}
    }
  return (res);
}