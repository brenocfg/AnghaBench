#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  current; } ;
typedef  TYPE_1__ FORM ;

/* Variables and functions */
 int E_OK ; 
 int /*<<< orphan*/  E_REQUEST_DENIED ; 
 int /*<<< orphan*/  SetStatus (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Single_Line_Field (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _NEWTOP ; 

__attribute__((used)) static int
Vertical_Scrolling(int (*const fct) (FORM *), FORM *form)
{
  int res = E_REQUEST_DENIED;

  if (!Single_Line_Field(form->current))
    {
      res = fct(form);
      if (res == E_OK)
	SetStatus(form, _NEWTOP);
    }
  return (res);
}