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
struct TYPE_4__ {int va_type; int /*<<< orphan*/  va_crtc_addr; } ;
typedef  TYPE_1__ video_adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATC ; 
 int /*<<< orphan*/  ENODEV ; 
#define  KD_CGA 132 
#define  KD_EGA 131 
#define  KD_HERCULES 130 
#define  KD_MONO 129 
#define  KD_VGA 128 
 int /*<<< orphan*/  V_ADP_BORDER ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prologue (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vga_set_border(video_adapter_t *adp, int color)
{
    prologue(adp, V_ADP_BORDER, ENODEV);

    switch (adp->va_type) {
    case KD_EGA:
    case KD_VGA:    
	inb(adp->va_crtc_addr + 6);	/* reset flip-flop */
	outb(ATC, 0x31); outb(ATC, color & 0xff); 
	break;  
    case KD_CGA:    
	outb(adp->va_crtc_addr + 5, color & 0x0f); /* color select register */
	break;  
    case KD_MONO:   
    case KD_HERCULES:
    default:
	break;  
    }
    return 0;
}