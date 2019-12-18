#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_4__ {int height; } ;
struct TYPE_3__ {int lfb_linelength; int lfb_height; } ;

/* Variables and functions */
 unsigned long* efi_earlycon_map (int,int) ; 
 int /*<<< orphan*/  efi_earlycon_unmap (unsigned long*,int) ; 
 TYPE_2__* font ; 
 int /*<<< orphan*/  memmove (unsigned long*,unsigned long*,int) ; 
 TYPE_1__ screen_info ; 

__attribute__((used)) static void efi_earlycon_scroll_up(void)
{
	unsigned long *dst, *src;
	u16 len;
	u32 i, height;

	len = screen_info.lfb_linelength;
	height = screen_info.lfb_height;

	for (i = 0; i < height - font->height; i++) {
		dst = efi_earlycon_map(i*len, len);
		if (!dst)
			return;

		src = efi_earlycon_map((i + font->height) * len, len);
		if (!src) {
			efi_earlycon_unmap(dst, len);
			return;
		}

		memmove(dst, src, len);

		efi_earlycon_unmap(src, len);
		efi_earlycon_unmap(dst, len);
	}
}