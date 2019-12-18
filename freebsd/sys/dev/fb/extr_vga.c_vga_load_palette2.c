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
 int /*<<< orphan*/  ATC ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  PALDATA ; 
 int /*<<< orphan*/  PALWADR ; 
 int /*<<< orphan*/  PIXMASK ; 
 int V_ADP_DAC8 ; 
 int /*<<< orphan*/  V_ADP_PALETTE ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prologue (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vga_load_palette2(video_adapter_t *adp, int base, int count,
		  u_char *r, u_char *g, u_char *b)
{
    int bits;
    int i;

    prologue(adp, V_ADP_PALETTE, ENODEV);

    outb(PIXMASK, 0xff);		/* no pixelmask */
    outb(PALWADR, base);
    bits = (adp->va_flags & V_ADP_DAC8) != 0 ? 0 : 2;
    for (i = 0; i < count; ++i) {
	outb(PALDATA, r[i] >> bits);
	outb(PALDATA, g[i] >> bits);
	outb(PALDATA, b[i] >> bits);
    }
    inb(adp->va_crtc_addr + 6);		/* reset flip/flop */
    outb(ATC, 0x20);			/* enable palette */
    return 0;
}