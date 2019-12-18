#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct TYPE_6__ {scalar_t__ va_type; } ;
typedef  TYPE_1__ video_adapter_t ;
typedef  int u_char ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ FONT_BUF ; 
 scalar_t__ KD_VGA ; 
 int PARAM_BUFSIZE ; 
 int /*<<< orphan*/  TSIDX ; 
 int /*<<< orphan*/  TSREG ; 
 int /*<<< orphan*/  V_ADP_FONT ; 
 int /*<<< orphan*/  bcopy_fromio (uintptr_t,int*,int) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prologue (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_font_mode (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  set_normal_mode (TYPE_1__*,int*) ; 
 int splhigh () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static int
vga_save_font(video_adapter_t *adp, int page, int fontsize, int fontwidth,
	      u_char *data, int ch, int count)
{
#ifndef VGA_NO_FONT_LOADING
    u_char buf[PARAM_BUFSIZE];
    vm_offset_t segment;
    int c;
#ifdef VGA_ALT_SEQACCESS
    int s;
    u_char val = 0;
#endif

    prologue(adp, V_ADP_FONT, ENODEV);

    if (fontsize < 14) {
	/* FONT_8 */
	fontsize = 8;
    } else if (fontsize >= 32) {
	fontsize = 32;
    } else if (fontsize >= 16) {
	/* FONT_16 */
	fontsize = 16;
    } else {
	/* FONT_14 */
	fontsize = 14;
    }

    if (page < 0 || page >= 8 || fontwidth != 8)
	return EINVAL;
    segment = FONT_BUF + 0x4000*page;
    if (page > 3)
	segment -= 0xe000;

#ifdef VGA_ALT_SEQACCESS
    if (adp->va_type == KD_VGA) {	/* what about EGA? XXX */
	s = splhigh();
	outb(TSIDX, 0x00); outb(TSREG, 0x01);
	outb(TSIDX, 0x01); val = inb(TSREG);	/* disable screen */
	outb(TSIDX, 0x01); outb(TSREG, val | 0x20);
	outb(TSIDX, 0x00); outb(TSREG, 0x03);
	splx(s);
    }
#endif

    set_font_mode(adp, buf);
    if (fontsize == 32) {
	bcopy_fromio((uintptr_t)segment + ch*32, data, fontsize*count);
    } else {
	for (c = ch; count > 0; ++c, --count) {
	    bcopy_fromio((uintptr_t)segment + c*32, data, fontsize);
	    data += fontsize;
	}
    }
    set_normal_mode(adp, buf);

#ifdef VGA_ALT_SEQACCESS
    if (adp->va_type == KD_VGA) {
	s = splhigh();
	outb(TSIDX, 0x00); outb(TSREG, 0x01);
	outb(TSIDX, 0x01); outb(TSREG, val & 0xdf);	/* enable screen */
	outb(TSIDX, 0x00); outb(TSREG, 0x03);
	splx(s);
    }
#endif

    return 0;
#else /* VGA_NO_FONT_LOADING */
    return ENODEV;
#endif /* VGA_NO_FONT_LOADING */
}