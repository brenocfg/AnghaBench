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
struct TYPE_3__ {int va_type; int /*<<< orphan*/  va_crtc_addr; } ;
typedef  TYPE_1__ video_adapter_t ;
typedef  int u_char ;

/* Variables and functions */
 int ENODEV ; 
#define  KD_CGA 136 
#define  KD_EGA 135 
#define  KD_HERCULES 134 
#define  KD_MONO 133 
#define  KD_VGA 132 
 int /*<<< orphan*/  TSIDX ; 
 int /*<<< orphan*/  TSREG ; 
#define  V_DISPLAY_BLANK 131 
#define  V_DISPLAY_ON 130 
#define  V_DISPLAY_STAND_BY 129 
#define  V_DISPLAY_SUSPEND 128 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int splhigh () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static int
vga_blank_display(video_adapter_t *adp, int mode)
{
    u_char val;
    int s;

    s = splhigh();
    switch (adp->va_type) {
    case KD_VGA:
	switch (mode) {
	case V_DISPLAY_SUSPEND:
	case V_DISPLAY_STAND_BY:
	    outb(TSIDX, 0x01);
	    val = inb(TSREG);
	    outb(TSIDX, 0x01);
	    outb(TSREG, val | 0x20);
	    outb(adp->va_crtc_addr, 0x17);
	    val = inb(adp->va_crtc_addr + 1);
	    outb(adp->va_crtc_addr + 1, val & ~0x80);
	    break;
	case V_DISPLAY_BLANK:
	    outb(TSIDX, 0x01);
	    val = inb(TSREG);
	    outb(TSIDX, 0x01);
	    outb(TSREG, val | 0x20);
	    break;
	case V_DISPLAY_ON:
	    outb(TSIDX, 0x01);
	    val = inb(TSREG);
	    outb(TSIDX, 0x01);
	    outb(TSREG, val & 0xDF);
	    outb(adp->va_crtc_addr, 0x17);
	    val = inb(adp->va_crtc_addr + 1);
	    outb(adp->va_crtc_addr + 1, val | 0x80);
	    break;
	}
	break;

    case KD_EGA:
	/* no support yet */
	splx(s);
	return ENODEV;

    case KD_CGA:
	switch (mode) {
	case V_DISPLAY_SUSPEND:
	case V_DISPLAY_STAND_BY:
	case V_DISPLAY_BLANK:
	    outb(adp->va_crtc_addr + 4, 0x25);
	    break;
	case V_DISPLAY_ON:
	    outb(adp->va_crtc_addr + 4, 0x2d);
	    break;
	}
	break;

    case KD_MONO:
    case KD_HERCULES:
	switch (mode) {
	case V_DISPLAY_SUSPEND:
	case V_DISPLAY_STAND_BY:
	case V_DISPLAY_BLANK:
	    outb(adp->va_crtc_addr + 4, 0x21);
	    break;
	case V_DISPLAY_ON:
	    outb(adp->va_crtc_addr + 4, 0x29);
	    break;
	}
	break;
    default:
	break;
    }
    splx(s);

    return 0;
}