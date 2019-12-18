#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u16 ;
struct TYPE_2__ {unsigned int lfb_linelength; } ;

/* Variables and functions */
 unsigned long* efi_earlycon_map (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  efi_earlycon_unmap (unsigned long*,unsigned int) ; 
 int /*<<< orphan*/  memset (unsigned long*,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__ screen_info ; 

__attribute__((used)) static void efi_earlycon_clear_scanline(unsigned int y)
{
	unsigned long *dst;
	u16 len;

	len = screen_info.lfb_linelength;
	dst = efi_earlycon_map(y*len, len);
	if (!dst)
		return;

	memset(dst, 0, len);
	efi_earlycon_unmap(dst, len);
}