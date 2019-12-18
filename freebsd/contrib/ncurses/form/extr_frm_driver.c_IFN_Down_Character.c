#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ drows; } ;
struct TYPE_6__ {scalar_t__ currow; TYPE_2__* current; } ;
typedef  TYPE_1__ FORM ;
typedef  TYPE_2__ FIELD ;

/* Variables and functions */
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  E_REQUEST_DENIED ; 
 scalar_t__ Field_Grown (TYPE_2__*,int) ; 
 int /*<<< orphan*/  Single_Line_Field (TYPE_2__*) ; 
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_CALLED (char*) ; 
 int /*<<< orphan*/  returnCode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
IFN_Down_Character(FORM *form)
{
  FIELD *field = form->current;

  T((T_CALLED("IFN_Down_Character(%p)"), (void *)form));
  if ((++(form->currow)) == field->drows)
    {
#if GROW_IF_NAVIGATE
      if (!Single_Line_Field(field) && Field_Grown(field, 1))
	returnCode(E_OK);
#endif
      --(form->currow);
      returnCode(E_REQUEST_DENIED);
    }
  returnCode(E_OK);
}