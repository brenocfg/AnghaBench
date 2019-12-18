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
 int /*<<< orphan*/  E_INVALID_FIELD ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_CALLED (char*) ; 
 scalar_t__ _nc_Internal_Validation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  returnCode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
FV_Validation(FORM *form)
{
  T((T_CALLED("FV_Validation(%p)"), (void *)form));
  if (_nc_Internal_Validation(form))
    returnCode(E_OK);
  else
    returnCode(E_INVALID_FIELD);
}