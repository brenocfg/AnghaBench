#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* OutputString ) (TYPE_1__*,char*) ;int /*<<< orphan*/  (* TestString ) (TYPE_1__*,char*) ;} ;
typedef  int /*<<< orphan*/  EFI_STATUS ;
typedef  char CHAR16 ;

/* Variables and functions */
 scalar_t__ EFI_ERROR (int /*<<< orphan*/ ) ; 
 TYPE_1__* conout ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,char*) ; 

void
efi_cons_efiputchar(int c)
{
	CHAR16 buf[2];
	EFI_STATUS status;

	buf[0] = c;
        buf[1] = 0;     /* terminate string */

	status = conout->TestString(conout, buf);
	if (EFI_ERROR(status))
		buf[0] = '?';
	conout->OutputString(conout, buf);
}