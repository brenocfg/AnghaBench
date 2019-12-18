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

/* Variables and functions */
 int ENXIO ; 
#define  KD_CGA 132 
#define  KD_EGA 131 
#define  KD_HERCULES 130 
#define  KD_MONO 129 
#define  KD_VGA 128 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  vga_init_done ; 

__attribute__((used)) static int
vga_set_hw_cursor_shape(video_adapter_t *adp, int base, int height,
			int celsize, int blink)
{
    int s;

    if (!vga_init_done)
	return ENXIO;

    s = spltty();
    switch (adp->va_type) {
    case KD_VGA:
    case KD_CGA:
    case KD_MONO:
    case KD_HERCULES:
    default:
	if (height <= 0) {
	    /* make the cursor invisible */
	    outb(adp->va_crtc_addr, 10);
	    outb(adp->va_crtc_addr + 1, 32);
	    outb(adp->va_crtc_addr, 11);
	    outb(adp->va_crtc_addr + 1, 0);
	} else {
	    outb(adp->va_crtc_addr, 10);
	    outb(adp->va_crtc_addr + 1, celsize - base - height);
	    outb(adp->va_crtc_addr, 11);
	    outb(adp->va_crtc_addr + 1, celsize - base - 1);
	}
	break;
    case KD_EGA:
	if (height <= 0) {
	    /* make the cursor invisible */
	    outb(adp->va_crtc_addr, 10);
	    outb(adp->va_crtc_addr + 1, celsize);
	    outb(adp->va_crtc_addr, 11);
	    outb(adp->va_crtc_addr + 1, 0);
	} else {
	    outb(adp->va_crtc_addr, 10);
	    outb(adp->va_crtc_addr + 1, celsize - base - height);
	    outb(adp->va_crtc_addr, 11);
	    outb(adp->va_crtc_addr + 1, celsize - base);
	}
	break;
    }
    splx(s);

    return 0;
}