#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ va_type; scalar_t__ va_crtc_addr; scalar_t__ va_window; } ;
typedef  TYPE_1__ video_adapter_t ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_9__ {int sdepth; int height; int /*<<< orphan*/ * index; int /*<<< orphan*/  palette; int /*<<< orphan*/ * data; scalar_t__ bank; TYPE_1__* adp; int /*<<< orphan*/ * vidmem; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATC ; 
 int /*<<< orphan*/  GDCIDX ; 
 scalar_t__ KD_EGA ; 
 scalar_t__ KD_VGA ; 
 int /*<<< orphan*/  TSIDX ; 
 int /*<<< orphan*/  bmp_DecodeLine (TYPE_5__*,int) ; 
 TYPE_5__ bmp_info ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vidd_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  vidd_load_palette (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vidd_set_win_org (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bmp_Draw(video_adapter_t *adp)
{
    int		line;
#if 0
    int		i;
#endif

    if (bmp_info.data == NULL) {	/* init failed, do nothing */
	return(1);
    }
    
    /* clear the screen */
    bmp_info.vidmem = (u_char *)adp->va_window;
    bmp_info.adp = adp;
    vidd_clear(adp);
    vidd_set_win_org(adp, 0);
    bmp_info.bank = 0;

    /* initialise the info structure for drawing */
    bmp_info.index = bmp_info.data;
    
    /* set the palette for our image */
    vidd_load_palette(adp, (u_char *)&bmp_info.palette);

#if 0
    /* XXX: this is ugly, but necessary for EGA/VGA 1bpp/4bpp modes */
    if ((adp->va_type == KD_EGA) || (adp->va_type == KD_VGA)) {
	inb(adp->va_crtc_addr + 6);		/* reset flip-flop */
	outb(ATC, 0x14);
	outb(ATC, 0);
	for (i = 0; i < 16; ++i) {
	    outb(ATC, i);
	    outb(ATC, i);
	}
	inb(adp->va_crtc_addr + 6);		/* reset flip-flop */
	outb(ATC, 0x20);			/* enable palette */

	outw(GDCIDX, 0x0f01);			/* set/reset enable */

	if (bmp_info.sdepth == 1)
	    outw(TSIDX, 0x0102);		/* unmask plane #0 */
    }
#endif

    for (line = 0; (line < bmp_info.height) && bmp_info.index; line++) {
	bmp_DecodeLine(&bmp_info, line);
    }
    return(0);
}