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
typedef  int /*<<< orphan*/  ch ;

/* Variables and functions */
 int RB_SERIAL ; 
 int /*<<< orphan*/ * buffer ; 
 int /*<<< orphan*/  efi_cons_efiputchar (int) ; 
 int /*<<< orphan*/  input_byte (unsigned char) ; 
 int mode ; 
 int /*<<< orphan*/  teken ; 
 int /*<<< orphan*/  teken_input (int /*<<< orphan*/ *,unsigned char*,int) ; 

void
efi_cons_putchar(int c)
{
	unsigned char ch = c;

	if ((mode & RB_SERIAL) != 0) {
		input_byte(ch);
		return;
	}

	if (buffer != NULL)
		teken_input(&teken, &ch, sizeof (ch));
	else
		efi_cons_efiputchar(c);
}