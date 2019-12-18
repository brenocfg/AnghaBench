#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  video_adapter_t ;
typedef  int u_char ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  TSIDX ; 
 int /*<<< orphan*/  TSREG ; 
 int /*<<< orphan*/  V_ADP_FONT ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prologue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int splhigh () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static int
vga_show_font(video_adapter_t *adp, int page)
{
#ifndef VGA_NO_FONT_LOADING
    static u_char cg[] = { 0x00, 0x05, 0x0a, 0x0f, 0x30, 0x35, 0x3a, 0x3f };
    int s;

    prologue(adp, V_ADP_FONT, ENODEV);
    if (page < 0 || page >= 8)
	return EINVAL;

    s = splhigh();
    outb(TSIDX, 0x03); outb(TSREG, cg[page]);
    splx(s);

    return 0;
#else /* VGA_NO_FONT_LOADING */
    return ENODEV;
#endif /* VGA_NO_FONT_LOADING */
}