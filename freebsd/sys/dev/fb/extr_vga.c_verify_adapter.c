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
typedef  scalar_t__ vm_offset_t ;
struct TYPE_3__ {int va_window; int va_type; char* va_name; int va_flags; int /*<<< orphan*/  va_crtc_addr; } ;
typedef  TYPE_1__ video_adapter_t ;
typedef  int u_int32_t ;
typedef  int u_int16_t ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 scalar_t__ BIOS_PADDRTOVADDR (int) ; 
 int BIOS_SADDRTOLADDR (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  ISMAPPED (int,int) ; 
#define  KD_CGA 130 
#define  KD_EGA 129 
#define  KD_MONO 128 
 int KD_VGA ; 
 int V_ADP_BORDER ; 
 int V_ADP_COLOR ; 
 int V_ADP_PALETTE ; 
 int V_ADP_STATELOAD ; 
 int V_ADP_STATESAVE ; 
 int V_MODE_PARAM_SIZE ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/ * video_mode_ptr ; 
 int /*<<< orphan*/ * video_mode_ptr2 ; 
 int /*<<< orphan*/  writew (scalar_t__,int) ; 

__attribute__((used)) static int
verify_adapter(video_adapter_t *adp)
{
    vm_offset_t buf;
    u_int16_t v;
#if !defined(VGA_NO_BIOS) && !defined(VGA_NO_MODE_CHANGE)
    u_int32_t p;
#endif

    buf = BIOS_PADDRTOVADDR(adp->va_window);
    v = readw(buf);
    writew(buf, 0xA55A);
    if (readw(buf) != 0xA55A)
	return ENXIO;
    writew(buf, v);

    switch (adp->va_type) {

    case KD_EGA:
	outb(adp->va_crtc_addr, 7);
	if (inb(adp->va_crtc_addr) == 7) {
	    adp->va_type = KD_VGA;
	    adp->va_name = "vga";
	    adp->va_flags |= V_ADP_STATESAVE | V_ADP_PALETTE;
	}
	adp->va_flags |= V_ADP_STATELOAD | V_ADP_BORDER;
	/* the color adapter may be in the 40x25 mode... XXX */

#if !defined(VGA_NO_BIOS) && !defined(VGA_NO_MODE_CHANGE)
	/* get the BIOS video mode pointer */
	p = *(u_int32_t *)BIOS_PADDRTOVADDR(0x4a8);
	p = BIOS_SADDRTOLADDR(p);
	if (ISMAPPED(p, sizeof(u_int32_t))) {
	    p = *(u_int32_t *)BIOS_PADDRTOVADDR(p);
	    p = BIOS_SADDRTOLADDR(p);
	    if (ISMAPPED(p, V_MODE_PARAM_SIZE))
		video_mode_ptr = (u_char *)BIOS_PADDRTOVADDR(p);
	}
#endif
	break;

    case KD_CGA:
	adp->va_flags |= V_ADP_COLOR | V_ADP_BORDER;
	/* may be in the 40x25 mode... XXX */
#if !defined(VGA_NO_BIOS) && !defined(VGA_NO_MODE_CHANGE)
	/* get the BIOS video mode pointer */
	p = *(u_int32_t *)BIOS_PADDRTOVADDR(0x1d*4);
	p = BIOS_SADDRTOLADDR(p);
	video_mode_ptr2 = (u_char *)BIOS_PADDRTOVADDR(p);
#endif
	break;

    case KD_MONO:
#if !defined(VGA_NO_BIOS) && !defined(VGA_NO_MODE_CHANGE)
	/* get the BIOS video mode pointer */
	p = *(u_int32_t *)BIOS_PADDRTOVADDR(0x1d*4);
	p = BIOS_SADDRTOLADDR(p);
	video_mode_ptr2 = (u_char *)BIOS_PADDRTOVADDR(p);
#endif
	break;
    }

    return 0;
}