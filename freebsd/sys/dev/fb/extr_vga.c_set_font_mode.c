#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ va_type; scalar_t__ va_crtc_addr; int /*<<< orphan*/  va_mode; } ;
typedef  TYPE_1__ video_adapter_t ;
typedef  int u_char ;

/* Variables and functions */
 scalar_t__ ATC ; 
 scalar_t__ GDCIDX ; 
 scalar_t__ GDCREG ; 
 scalar_t__ KD_VGA ; 
 scalar_t__ TSIDX ; 
 scalar_t__ TSREG ; 
 int* get_mode_param (int /*<<< orphan*/ ) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (scalar_t__,int) ; 
 int /*<<< orphan*/  outw (scalar_t__,int) ; 
 int splhigh () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static void
set_font_mode(video_adapter_t *adp, u_char *buf)
{
    u_char *mp;
    int s;

    s = splhigh();

    /* save register values */
    if (adp->va_type == KD_VGA) {
	outb(TSIDX, 0x02); buf[0] = inb(TSREG);
	outb(TSIDX, 0x04); buf[1] = inb(TSREG);
	outb(GDCIDX, 0x04); buf[2] = inb(GDCREG);
	outb(GDCIDX, 0x05); buf[3] = inb(GDCREG);
	outb(GDCIDX, 0x06); buf[4] = inb(GDCREG);
	inb(adp->va_crtc_addr + 6);
	outb(ATC, 0x10); buf[5] = inb(ATC + 1);
    } else /* if (adp->va_type == KD_EGA) */ {
	/* 
	 * EGA cannot be read; copy parameters from the mode parameter 
	 * table. 
	 */
	mp = get_mode_param(adp->va_mode);
	buf[0] = mp[5 + 0x02 - 1];
	buf[1] = mp[5 + 0x04 - 1];
	buf[2] = mp[55 + 0x04];
	buf[3] = mp[55 + 0x05];
	buf[4] = mp[55 + 0x06];
	buf[5] = mp[35 + 0x10];
    }

    /* setup vga for loading fonts */
    inb(adp->va_crtc_addr + 6);			/* reset flip-flop */
    outb(ATC, 0x10); outb(ATC, buf[5] & ~0x01);
    inb(adp->va_crtc_addr + 6);			/* reset flip-flop */
    outb(ATC, 0x20);				/* enable palette */

#ifdef VGA_SLOW_IOACCESS
#ifdef VGA_ALT_SEQACCESS
    outb(TSIDX, 0x00); outb(TSREG, 0x01);
#endif
    outb(TSIDX, 0x02); outb(TSREG, 0x04);
    outb(TSIDX, 0x04); outb(TSREG, 0x07);
#ifdef VGA_ALT_SEQACCESS
    outb(TSIDX, 0x00); outb(TSREG, 0x03);
#endif
    outb(GDCIDX, 0x04); outb(GDCREG, 0x02);
    outb(GDCIDX, 0x05); outb(GDCREG, 0x00);
    outb(GDCIDX, 0x06); outb(GDCREG, 0x04);
#else /* VGA_SLOW_IOACCESS */
#ifdef VGA_ALT_SEQACCESS
    outw(TSIDX, 0x0100);
#endif
    outw(TSIDX, 0x0402);
    outw(TSIDX, 0x0704);
#ifdef VGA_ALT_SEQACCESS
    outw(TSIDX, 0x0300);
#endif
    outw(GDCIDX, 0x0204);
    outw(GDCIDX, 0x0005);
    outw(GDCIDX, 0x0406);               /* addr = a0000, 64kb */
#endif /* VGA_SLOW_IOACCESS */

    splx(s);
}