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
typedef  int u8 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  suspend_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  DACR ; 
 int /*<<< orphan*/  HD64461_PCC1CSCIER ; 
 int /*<<< orphan*/  HD64461_PCC1CSCR ; 
 int /*<<< orphan*/  HD64461_PCC1SCR ; 
 int HD64461_PCCSCR_VCC1 ; 
 int /*<<< orphan*/  HD64461_SCPUCR ; 
 int /*<<< orphan*/  HD64461_STBCR ; 
 int HD64461_STBCR_SPC1ST ; 
 int /*<<< orphan*/  STBCR ; 
 int /*<<< orphan*/  STBCR2 ; 
 int __raw_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writeb (int,int /*<<< orphan*/ ) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_enter () ; 

__attribute__((used)) static int hp6x0_pm_enter(suspend_state_t state)
{
	u8 stbcr, stbcr2;
#ifdef CONFIG_HD64461_ENABLER
	u8 scr;
	u16 hd64461_stbcr;
#endif

#ifdef CONFIG_HD64461_ENABLER
	outb(0, HD64461_PCC1CSCIER);

	scr = inb(HD64461_PCC1SCR);
	scr |= HD64461_PCCSCR_VCC1;
	outb(scr, HD64461_PCC1SCR);

	hd64461_stbcr = inw(HD64461_STBCR);
	hd64461_stbcr |= HD64461_STBCR_SPC1ST;
	outw(hd64461_stbcr, HD64461_STBCR);
#endif

	__raw_writeb(0x1f, DACR);

	stbcr = __raw_readb(STBCR);
	__raw_writeb(0x01, STBCR);

	stbcr2 = __raw_readb(STBCR2);
	__raw_writeb(0x7f , STBCR2);

	outw(0xf07f, HD64461_SCPUCR);

	pm_enter();

	outw(0, HD64461_SCPUCR);
	__raw_writeb(stbcr, STBCR);
	__raw_writeb(stbcr2, STBCR2);

#ifdef CONFIG_HD64461_ENABLER
	hd64461_stbcr = inw(HD64461_STBCR);
	hd64461_stbcr &= ~HD64461_STBCR_SPC1ST;
	outw(hd64461_stbcr, HD64461_STBCR);

	outb(0x4c, HD64461_PCC1CSCIER);
	outb(0x00, HD64461_PCC1CSCR);
#endif

	return 0;
}