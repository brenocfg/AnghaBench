#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int vi_flags; int vi_width; int vi_cwidth; int vi_height; int vi_cheight; } ;
typedef  TYPE_1__ video_info_t ;
struct TYPE_9__ {int va_crtc_addr; int /*<<< orphan*/  va_mode; } ;
typedef  TYPE_2__ video_adapter_t ;
typedef  int u_char ;
struct TYPE_10__ {int* regs; int /*<<< orphan*/  sig; } ;
typedef  TYPE_3__ adp_state_t ;

/* Variables and functions */
 int ATC ; 
 int /*<<< orphan*/  BIOS_PADDRTOVADDR (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 int GDCIDX ; 
 int GDCREG ; 
 int MISC ; 
 int TSIDX ; 
 int TSREG ; 
 int /*<<< orphan*/  V_ADP_STATESAVE ; 
 int V_INFO_GRAPHICS ; 
 int /*<<< orphan*/  V_MODE_PARAM_SIZE ; 
 int /*<<< orphan*/  V_STATE_SIG ; 
 int /*<<< orphan*/  bzero (int*,int /*<<< orphan*/ ) ; 
 int inb (int) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  prologue (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readb (int /*<<< orphan*/ ) ; 
 int splhigh () ; 
 int /*<<< orphan*/  splx (int) ; 
 scalar_t__ vga_get_info (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
vga_save_state(video_adapter_t *adp, void *p, size_t size)
{
    video_info_t info;
    u_char *buf;
    int crtc_addr;
    int i, j;
    int s;

    if (size == 0) {
	/* return the required buffer size */
	prologue(adp, V_ADP_STATESAVE, 0);
	return sizeof(adp_state_t);
    } else {
	prologue(adp, V_ADP_STATESAVE, ENODEV);
	if (size < sizeof(adp_state_t))
	    return EINVAL;
    }

    ((adp_state_t *)p)->sig = V_STATE_SIG;
    buf = ((adp_state_t *)p)->regs;
    bzero(buf, V_MODE_PARAM_SIZE);
    crtc_addr = adp->va_crtc_addr;

    s = splhigh();

    outb(TSIDX, 0x00); outb(TSREG, 0x01);	/* stop sequencer */
    for (i = 0, j = 5; i < 4; i++) {           
	outb(TSIDX, i + 1);
	buf[j++]  =  inb(TSREG);
    }
    buf[9]  =  inb(MISC + 10);			/* dot-clock */
    outb(TSIDX, 0x00); outb(TSREG, 0x03);	/* start sequencer */

    for (i = 0, j = 10; i < 25; i++) {		/* crtc */
	outb(crtc_addr, i);
	buf[j++]  =  inb(crtc_addr + 1);
    }
    for (i = 0, j = 35; i < 20; i++) {		/* attribute ctrl */
        inb(crtc_addr + 6);			/* reset flip-flop */
	outb(ATC, i);
	buf[j++]  =  inb(ATC + 1);
    }
    for (i = 0, j = 55; i < 9; i++) {		/* graph data ctrl */
	outb(GDCIDX, i);
	buf[j++]  =  inb(GDCREG);
    }
    inb(crtc_addr + 6);				/* reset flip-flop */
    outb(ATC, 0x20);				/* enable palette */

    splx(s);

#if 1
    if (vga_get_info(adp, adp->va_mode, &info) == 0) {
	if (info.vi_flags & V_INFO_GRAPHICS) {
	    buf[0] = info.vi_width/info.vi_cwidth; /* COLS */
	    buf[1] = info.vi_height/info.vi_cheight - 1; /* ROWS */
	} else {
	    buf[0] = info.vi_width;		/* COLS */
	    buf[1] = info.vi_height - 1;	/* ROWS */
	}
	buf[2] = info.vi_cheight;		/* POINTS */
    }
#else
    buf[0] = readb(BIOS_PADDRTOVADDR(0x44a));	/* COLS */
    buf[1] = readb(BIOS_PADDRTOVADDR(0x484));	/* ROWS */
    buf[2] = readb(BIOS_PADDRTOVADDR(0x485));	/* POINTS */
    buf[3] = readb(BIOS_PADDRTOVADDR(0x44c));
    buf[4] = readb(BIOS_PADDRTOVADDR(0x44d));
#endif

    return 0;
}