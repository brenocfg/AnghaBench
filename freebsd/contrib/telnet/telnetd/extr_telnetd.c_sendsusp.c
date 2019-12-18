#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__* sptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTSTP ; 
 size_t SLC_SUSP ; 
 int /*<<< orphan*/  TCSIG ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfrontp ; 
 int /*<<< orphan*/  pty ; 
 int /*<<< orphan*/  ptyflush () ; 
 TYPE_1__* slctab ; 

void
sendsusp(void)
{
#ifdef	SIGTSTP
	ptyflush();	/* half-hearted */
# ifdef	TCSIG
	(void) ioctl(pty, TCSIG, SIGTSTP);
# else	/* TCSIG */
	*pfrontp++ = slctab[SLC_SUSP].sptr ?
			(unsigned char)*slctab[SLC_SUSP].sptr : '\032';
# endif	/* TCSIG */
#endif	/* SIGTSTP */
}