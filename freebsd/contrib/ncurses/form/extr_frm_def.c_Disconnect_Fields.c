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
typedef  int /*<<< orphan*/  _PAGE ;
struct TYPE_5__ {TYPE_1__* form; } ;
struct TYPE_4__ {int maxfield; int maxpage; int /*<<< orphan*/ * page; TYPE_2__** field; scalar_t__ cols; scalar_t__ rows; } ;
typedef  TYPE_1__ FORM ;
typedef  TYPE_2__ FIELD ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
Disconnect_Fields(FORM *form)
{
  if (form->field)
    {
      FIELD **fields;

      for (fields = form->field; *fields; fields++)
	{
	  if (form == (*fields)->form)
	    (*fields)->form = (FORM *)0;
	}

      form->rows = form->cols = 0;
      form->maxfield = form->maxpage = -1;
      form->field = (FIELD **)0;
      if (form->page)
	free(form->page);
      form->page = (_PAGE *) 0;
    }
}