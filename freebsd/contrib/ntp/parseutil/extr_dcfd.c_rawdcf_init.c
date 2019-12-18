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
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int CIOCM_DTR ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  TIOCMSET ; 
 int TIOCM_DTR ; 
 int ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
rawdcf_init(
	int fd
	)
{
	/*
	 * You can use the RS232 to supply the power for a DCF77 receiver.
	 * Here a voltage between the DTR and the RTS line is used. Unfortunately
	 * the name has changed from CIOCM_DTR to TIOCM_DTR recently.
	 */

#ifdef TIOCM_DTR
	int sl232 = TIOCM_DTR;	/* turn on DTR for power supply */
#else
	int sl232 = CIOCM_DTR;	/* turn on DTR for power supply */
#endif

	if (ioctl(fd, TIOCMSET, (caddr_t)&sl232) == -1)
	{
		syslog(LOG_NOTICE, "rawdcf_init: WARNING: ioctl(fd, TIOCMSET, [C|T]IOCM_DTR): %m");
	}
}