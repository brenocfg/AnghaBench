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
struct TYPE_4__ {int va_flags; scalar_t__ va_crtc_addr; } ;
typedef  TYPE_1__ video_adapter_t ;
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 scalar_t__ PALDATA ; 
 int /*<<< orphan*/  PALRADR ; 
 int V_ADP_DAC8 ; 
 int /*<<< orphan*/  V_ADP_PALETTE ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prologue (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vga_save_palette(video_adapter_t *adp, u_char *palette)
{
    int bits;
    int i;

    prologue(adp, V_ADP_PALETTE, ENODEV);

    /* 
     * We store 8 bit values in the palette buffer, while the standard
     * VGA has 6 bit DAC .
     */
    outb(PALRADR, 0x00);
    bits = (adp->va_flags & V_ADP_DAC8) != 0 ? 0 : 2;
    for (i = 0; i < 256*3; ++i)
	palette[i] = inb(PALDATA) << bits; 
    inb(adp->va_crtc_addr + 6);	/* reset flip/flop */
    return 0;
}