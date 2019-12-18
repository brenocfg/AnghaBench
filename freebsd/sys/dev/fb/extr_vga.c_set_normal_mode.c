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
struct TYPE_3__ {scalar_t__ va_crtc_addr; } ;
typedef  TYPE_1__ video_adapter_t ;
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  ATC ; 
 int /*<<< orphan*/  GDCIDX ; 
 int /*<<< orphan*/  GDCREG ; 
 scalar_t__ MONO_CRTC ; 
 int /*<<< orphan*/  TSIDX ; 
 int /*<<< orphan*/  TSREG ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,int) ; 
 int splhigh () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static void
set_normal_mode(video_adapter_t *adp, u_char *buf)
{
    int s;

    s = splhigh();

    /* setup vga for normal operation mode again */
    inb(adp->va_crtc_addr + 6);			/* reset flip-flop */
    outb(ATC, 0x10); outb(ATC, buf[5]);
    inb(adp->va_crtc_addr + 6);			/* reset flip-flop */
    outb(ATC, 0x20);				/* enable palette */

#ifdef VGA_SLOW_IOACCESS
#ifdef VGA_ALT_SEQACCESS
    outb(TSIDX, 0x00); outb(TSREG, 0x01);
#endif
    outb(TSIDX, 0x02); outb(TSREG, buf[0]);
    outb(TSIDX, 0x04); outb(TSREG, buf[1]);
#ifdef VGA_ALT_SEQACCESS
    outb(TSIDX, 0x00); outb(TSREG, 0x03);
#endif
    outb(GDCIDX, 0x04); outb(GDCREG, buf[2]);
    outb(GDCIDX, 0x05); outb(GDCREG, buf[3]);
    if (adp->va_crtc_addr == MONO_CRTC) {
	outb(GDCIDX, 0x06); outb(GDCREG,(buf[4] & 0x03) | 0x08);
    } else {
	outb(GDCIDX, 0x06); outb(GDCREG,(buf[4] & 0x03) | 0x0c);
    }
#else /* VGA_SLOW_IOACCESS */
#ifdef VGA_ALT_SEQACCESS
    outw(TSIDX, 0x0100);
#endif
    outw(TSIDX, 0x0002 | (buf[0] << 8));
    outw(TSIDX, 0x0004 | (buf[1] << 8));
#ifdef VGA_ALT_SEQACCESS
    outw(TSIDX, 0x0300);
#endif
    outw(GDCIDX, 0x0004 | (buf[2] << 8));
    outw(GDCIDX, 0x0005 | (buf[3] << 8));
    if (adp->va_crtc_addr == MONO_CRTC)
        outw(GDCIDX, 0x0006 | (((buf[4] & 0x03) | 0x08)<<8));
    else
        outw(GDCIDX, 0x0006 | (((buf[4] & 0x03) | 0x0c)<<8));
#endif /* VGA_SLOW_IOACCESS */

    splx(s);
}