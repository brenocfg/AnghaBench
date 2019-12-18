#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  FORM ;

/* Variables and functions */
 int /*<<< orphan*/  Call_Hook (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int E_INVALID_FIELD ; 
 int /*<<< orphan*/  _nc_Internal_Validation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fieldinit ; 
 int /*<<< orphan*/  fieldterm ; 

__attribute__((used)) static int
Inter_Field_Navigation(int (*const fct) (FORM *), FORM *form)
{
  int res;

  if (!_nc_Internal_Validation(form))
    res = E_INVALID_FIELD;
  else
    {
      Call_Hook(form, fieldterm);
      res = fct(form);
      Call_Hook(form, fieldinit);
    }
  return res;
}