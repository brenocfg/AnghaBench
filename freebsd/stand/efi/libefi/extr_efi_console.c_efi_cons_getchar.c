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

/* Variables and functions */
 int /*<<< orphan*/ * coninex ; 
 scalar_t__ efi_readkey () ; 
 scalar_t__ efi_readkey_ex () ; 
 scalar_t__ key_pending ; 
 int keybuf_getchar () ; 

int
efi_cons_getchar(void)
{
	int c;

	if ((c = keybuf_getchar()) != 0)
		return (c);

	key_pending = 0;

	if (coninex == NULL) {
		if (efi_readkey())
			return (keybuf_getchar());
	} else {
		if (efi_readkey_ex())
			return (keybuf_getchar());
	}

	return (-1);
}