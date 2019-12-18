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
 int /*<<< orphan*/  SIGINFO ; 
 size_t SLC_AYT ; 
 int /*<<< orphan*/  TCSIG ; 
 scalar_t__ _POSIX_VDISABLE ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_data (char*) ; 
 int /*<<< orphan*/  pty ; 
 TYPE_1__* slctab ; 

void
recv_ayt(void)
{
#if	defined(SIGINFO) && defined(TCSIG)
	if (slctab[SLC_AYT].sptr && *slctab[SLC_AYT].sptr != _POSIX_VDISABLE) {
		(void) ioctl(pty, TCSIG, SIGINFO);
		return;
	}
#endif
	output_data("\r\n[Yes]\r\n");
}