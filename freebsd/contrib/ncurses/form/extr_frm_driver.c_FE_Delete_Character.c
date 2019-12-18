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
 int /*<<< orphan*/  DeleteChar (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_CALLED (char*) ; 
 int /*<<< orphan*/  returnCode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
FE_Delete_Character(FORM *form)
{
  T((T_CALLED("FE_Delete_Character(%p)"), (void *)form));
  DeleteChar(form);
  returnCode(E_OK);
}