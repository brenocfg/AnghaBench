#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINTN ;
struct TYPE_6__ {int /*<<< orphan*/  (* EnableCursor ) (TYPE_2__*,int /*<<< orphan*/ ) ;TYPE_1__* Mode; int /*<<< orphan*/  (* QueryMode ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {int CursorColumn; int /*<<< orphan*/  Mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* conout ; 
 int /*<<< orphan*/  curx ; 
 int /*<<< orphan*/  cury ; 
 int /*<<< orphan*/  efi_cons_efiputchar (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
efi_cons_rawputchar(int c)
{
	int i;
	UINTN x, y;
	conout->QueryMode(conout, conout->Mode->Mode, &x, &y);

	if (c == '\t') {
		int n;

		n = 8 - ((conout->Mode->CursorColumn + 8) % 8);
		for (i = 0; i < n; i++)
			efi_cons_rawputchar(' ');
	} else {
#ifndef TERM_EMU
		if (c == '\n')
			efi_cons_efiputchar('\r');
		efi_cons_efiputchar(c);
#else
		switch (c) {
		case '\r':
			curx = 0;
			efi_cons_efiputchar('\r');
			return;
		case '\n':
			efi_cons_efiputchar('\n');
			efi_cons_efiputchar('\r');
			cury++;
			if (cury >= y)
				cury--;
			curx = 0;
			return;
		case '\b':
			if (curx > 0) {
				efi_cons_efiputchar('\b');
				curx--;
			}
			return;
		default:
			efi_cons_efiputchar(c);
			curx++;
			if (curx > x-1) {
				curx = 0;
				cury++;
			}
			if (cury > y-1) {
				curx = 0;
				cury--;
			}
		}
#endif
	}
	conout->EnableCursor(conout, TRUE);
}