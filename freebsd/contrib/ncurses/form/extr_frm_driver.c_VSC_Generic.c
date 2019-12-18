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
struct TYPE_5__ {int drows; int rows; } ;
struct TYPE_4__ {int toprow; int currow; TYPE_2__* current; } ;
typedef  TYPE_1__ FORM ;
typedef  TYPE_2__ FIELD ;

/* Variables and functions */
 int E_OK ; 
 int E_REQUEST_DENIED ; 

__attribute__((used)) static int
VSC_Generic(FORM *form, int nlines)
{
  FIELD *field = form->current;
  int res = E_REQUEST_DENIED;
  int rows_to_go = (nlines > 0 ? nlines : -nlines);

  if (nlines > 0)
    {
      if ((rows_to_go + form->toprow) > (field->drows - field->rows))
	rows_to_go = (field->drows - field->rows - form->toprow);

      if (rows_to_go > 0)
	{
	  form->currow += rows_to_go;
	  form->toprow += rows_to_go;
	  res = E_OK;
	}
    }
  else
    {
      if (rows_to_go > form->toprow)
	rows_to_go = form->toprow;

      if (rows_to_go > 0)
	{
	  form->currow -= rows_to_go;
	  form->toprow -= rows_to_go;
	  res = E_OK;
	}
    }
  return (res);
}