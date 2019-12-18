#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int vi_mem_model; int vi_depth; int vi_planes; } ;
struct TYPE_5__ {scalar_t__ va_type; int va_line_width; scalar_t__ va_crtc_addr; TYPE_1__ va_info; int /*<<< orphan*/  va_mode; } ;
typedef  TYPE_2__ video_adapter_t ;
typedef  int u_char ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ KD_EGA ; 
 scalar_t__ KD_VGA ; 
#define  V_INFO_MM_PACKED 130 
#define  V_INFO_MM_PLANAR 129 
#define  V_INFO_MM_TEXT 128 
 int* get_mode_param (int /*<<< orphan*/ ) ; 
 int howmany (int,int) ; 
 int /*<<< orphan*/  outb (scalar_t__,int) ; 
 int rounddown (int,int) ; 

__attribute__((used)) static int
set_line_length(video_adapter_t *adp, int pixel)
{
    u_char *mp;
    int ppw;	/* pixels per word */
    int bpl;	/* bytes per line */
    int count;

    if ((adp->va_type != KD_VGA) && (adp->va_type != KD_EGA))
	return ENODEV;
    mp = get_mode_param(adp->va_mode);
    if (mp == NULL)
	return EINVAL;

    switch (adp->va_info.vi_mem_model) {
    case V_INFO_MM_PLANAR:
	ppw = 16/(adp->va_info.vi_depth/adp->va_info.vi_planes);
	count = howmany(pixel, ppw)/2;
	bpl = (howmany(pixel, ppw)/2)*4;
	break;
    case V_INFO_MM_PACKED:
	count = (pixel + 7)/8;
	bpl = rounddown(pixel + 7, 8);
	break;
    case V_INFO_MM_TEXT:
	count = (pixel + 7)/8;			/* columns */
	bpl = (pixel + 7)/8;			/* columns */
	break;
    default:
	return ENODEV;
    }

    if (mp[10 + 0x17] & 0x40)			/* CRTC mode control reg */
	count *= 2;				/* byte mode */
    outb(adp->va_crtc_addr, 0x13);
    outb(adp->va_crtc_addr + 1, count);
    adp->va_line_width = bpl;

    return 0;
}