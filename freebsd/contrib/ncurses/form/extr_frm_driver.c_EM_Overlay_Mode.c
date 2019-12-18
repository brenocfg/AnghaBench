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
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  SetStatus (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_CALLED (char*) ; 
 int /*<<< orphan*/  _OVLMODE ; 
 int /*<<< orphan*/  returnCode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
EM_Overlay_Mode(FORM *form)
{
  T((T_CALLED("EM_Overlay_Mode(%p)"), (void *)form));
  SetStatus(form, _OVLMODE);
  returnCode(E_OK);
}