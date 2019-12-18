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
struct termios {int c_cflag; scalar_t__* c_cc; int /*<<< orphan*/  c_ospeed; int /*<<< orphan*/  c_ispeed; int /*<<< orphan*/  c_lflag; int /*<<< orphan*/  c_oflag; int /*<<< orphan*/  c_iflag; } ;
struct linux_termios {int c_iflag; int c_oflag; int c_cflag; int c_lflag; scalar_t__* c_cc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRKINT ; 
 int CLOCAL ; 
 int CREAD ; 
 int CRTSCTS ; 
 int CSTOPB ; 
 int /*<<< orphan*/  ECHO ; 
 int /*<<< orphan*/  ECHOCTL ; 
 int /*<<< orphan*/  ECHOE ; 
 int /*<<< orphan*/  ECHOK ; 
 int /*<<< orphan*/  ECHOKE ; 
 int /*<<< orphan*/  ECHONL ; 
 int /*<<< orphan*/  ECHOPRT ; 
 int /*<<< orphan*/  FLUSHO ; 
 int HUPCL ; 
 int /*<<< orphan*/  ICANON ; 
 int /*<<< orphan*/  ICRNL ; 
 int /*<<< orphan*/  IEXTEN ; 
 int /*<<< orphan*/  IGNBRK ; 
 int /*<<< orphan*/  IGNCR ; 
 int /*<<< orphan*/  IGNPAR ; 
 int /*<<< orphan*/  IMAXBEL ; 
 int /*<<< orphan*/  INLCR ; 
 int /*<<< orphan*/  INPCK ; 
 int /*<<< orphan*/  ISIG ; 
 int /*<<< orphan*/  ISTRIP ; 
 int /*<<< orphan*/  IXANY ; 
 int /*<<< orphan*/  IXOFF ; 
 int /*<<< orphan*/  IXON ; 
 int LINUX_BRKINT ; 
 int LINUX_CBAUD ; 
 int LINUX_CLOCAL ; 
 int LINUX_CREAD ; 
 int LINUX_CRTSCTS ; 
 int LINUX_CSIZE ; 
 int LINUX_CSTOPB ; 
 int LINUX_ECHO ; 
 int LINUX_ECHOCTL ; 
 int LINUX_ECHOE ; 
 int LINUX_ECHOK ; 
 int LINUX_ECHOKE ; 
 int LINUX_ECHONL ; 
 int LINUX_ECHOPRT ; 
 int LINUX_FLUSHO ; 
 int LINUX_HUPCL ; 
 int LINUX_ICANON ; 
 int LINUX_ICRNL ; 
 int LINUX_IEXTEN ; 
 int LINUX_IGNBRK ; 
 int LINUX_IGNCR ; 
 int LINUX_IGNPAR ; 
 int LINUX_IMAXBEL ; 
 int LINUX_INLCR ; 
 int LINUX_INPCK ; 
 int LINUX_ISIG ; 
 int LINUX_ISTRIP ; 
 int LINUX_IXANY ; 
 int LINUX_IXOFF ; 
 int LINUX_IXON ; 
 int LINUX_NOFLSH ; 
 int LINUX_ONLCR ; 
 int LINUX_OPOST ; 
 int LINUX_PARENB ; 
 int LINUX_PARMRK ; 
 int LINUX_PARODD ; 
 int LINUX_PENDIN ; 
 scalar_t__ LINUX_POSIX_VDISABLE ; 
 int LINUX_TOSTOP ; 
 size_t LINUX_VDISCARD ; 
 size_t LINUX_VEOF ; 
 size_t LINUX_VEOL ; 
 size_t LINUX_VEOL2 ; 
 size_t LINUX_VERASE ; 
 size_t LINUX_VINTR ; 
 size_t LINUX_VKILL ; 
 size_t LINUX_VLNEXT ; 
 size_t LINUX_VMIN ; 
 size_t LINUX_VQUIT ; 
 size_t LINUX_VREPRINT ; 
 size_t LINUX_VSTART ; 
 size_t LINUX_VSTOP ; 
 size_t LINUX_VSUSP ; 
 size_t LINUX_VTIME ; 
 size_t LINUX_VWERASE ; 
 int LINUX_XTABS ; 
 int NCCS ; 
 int /*<<< orphan*/  NOFLSH ; 
 int /*<<< orphan*/  ONLCR ; 
 int /*<<< orphan*/  OPOST ; 
 int PARENB ; 
 int /*<<< orphan*/  PARMRK ; 
 int PARODD ; 
 int /*<<< orphan*/  PENDIN ; 
 int /*<<< orphan*/  TAB3 ; 
 int /*<<< orphan*/  TOSTOP ; 
 size_t VDISCARD ; 
 size_t VEOF ; 
 size_t VEOL ; 
 size_t VEOL2 ; 
 size_t VERASE ; 
 size_t VINTR ; 
 size_t VKILL ; 
 size_t VLNEXT ; 
 size_t VMIN ; 
 size_t VQUIT ; 
 size_t VREPRINT ; 
 size_t VSTART ; 
 size_t VSTOP ; 
 size_t VSUSP ; 
 size_t VTIME ; 
 size_t VWERASE ; 
 void* _POSIX_VDISABLE ; 
 int /*<<< orphan*/  linux_to_bsd_speed (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sptab ; 

__attribute__((used)) static void
linux_to_bsd_termios(struct linux_termios *lios, struct termios *bios)
{
	int i;

	bios->c_iflag = 0;
	if (lios->c_iflag & LINUX_IGNBRK)
		bios->c_iflag |= IGNBRK;
	if (lios->c_iflag & LINUX_BRKINT)
		bios->c_iflag |= BRKINT;
	if (lios->c_iflag & LINUX_IGNPAR)
		bios->c_iflag |= IGNPAR;
	if (lios->c_iflag & LINUX_PARMRK)
		bios->c_iflag |= PARMRK;
	if (lios->c_iflag & LINUX_INPCK)
		bios->c_iflag |= INPCK;
	if (lios->c_iflag & LINUX_ISTRIP)
		bios->c_iflag |= ISTRIP;
	if (lios->c_iflag & LINUX_INLCR)
		bios->c_iflag |= INLCR;
	if (lios->c_iflag & LINUX_IGNCR)
		bios->c_iflag |= IGNCR;
	if (lios->c_iflag & LINUX_ICRNL)
		bios->c_iflag |= ICRNL;
	if (lios->c_iflag & LINUX_IXON)
		bios->c_iflag |= IXON;
	if (lios->c_iflag & LINUX_IXANY)
		bios->c_iflag |= IXANY;
	if (lios->c_iflag & LINUX_IXOFF)
		bios->c_iflag |= IXOFF;
	if (lios->c_iflag & LINUX_IMAXBEL)
		bios->c_iflag |= IMAXBEL;

	bios->c_oflag = 0;
	if (lios->c_oflag & LINUX_OPOST)
		bios->c_oflag |= OPOST;
	if (lios->c_oflag & LINUX_ONLCR)
		bios->c_oflag |= ONLCR;
	if (lios->c_oflag & LINUX_XTABS)
		bios->c_oflag |= TAB3;

	bios->c_cflag = (lios->c_cflag & LINUX_CSIZE) << 4;
	if (lios->c_cflag & LINUX_CSTOPB)
		bios->c_cflag |= CSTOPB;
	if (lios->c_cflag & LINUX_CREAD)
		bios->c_cflag |= CREAD;
	if (lios->c_cflag & LINUX_PARENB)
		bios->c_cflag |= PARENB;
	if (lios->c_cflag & LINUX_PARODD)
		bios->c_cflag |= PARODD;
	if (lios->c_cflag & LINUX_HUPCL)
		bios->c_cflag |= HUPCL;
	if (lios->c_cflag & LINUX_CLOCAL)
		bios->c_cflag |= CLOCAL;
	if (lios->c_cflag & LINUX_CRTSCTS)
		bios->c_cflag |= CRTSCTS;

	bios->c_lflag = 0;
	if (lios->c_lflag & LINUX_ISIG)
		bios->c_lflag |= ISIG;
	if (lios->c_lflag & LINUX_ICANON)
		bios->c_lflag |= ICANON;
	if (lios->c_lflag & LINUX_ECHO)
		bios->c_lflag |= ECHO;
	if (lios->c_lflag & LINUX_ECHOE)
		bios->c_lflag |= ECHOE;
	if (lios->c_lflag & LINUX_ECHOK)
		bios->c_lflag |= ECHOK;
	if (lios->c_lflag & LINUX_ECHONL)
		bios->c_lflag |= ECHONL;
	if (lios->c_lflag & LINUX_NOFLSH)
		bios->c_lflag |= NOFLSH;
	if (lios->c_lflag & LINUX_TOSTOP)
		bios->c_lflag |= TOSTOP;
	if (lios->c_lflag & LINUX_ECHOCTL)
		bios->c_lflag |= ECHOCTL;
	if (lios->c_lflag & LINUX_ECHOPRT)
		bios->c_lflag |= ECHOPRT;
	if (lios->c_lflag & LINUX_ECHOKE)
		bios->c_lflag |= ECHOKE;
	if (lios->c_lflag & LINUX_FLUSHO)
		bios->c_lflag |= FLUSHO;
	if (lios->c_lflag & LINUX_PENDIN)
		bios->c_lflag |= PENDIN;
	if (lios->c_lflag & LINUX_IEXTEN)
		bios->c_lflag |= IEXTEN;

	for (i=0; i<NCCS; i++)
		bios->c_cc[i] = _POSIX_VDISABLE;
	bios->c_cc[VINTR] = lios->c_cc[LINUX_VINTR];
	bios->c_cc[VQUIT] = lios->c_cc[LINUX_VQUIT];
	bios->c_cc[VERASE] = lios->c_cc[LINUX_VERASE];
	bios->c_cc[VKILL] = lios->c_cc[LINUX_VKILL];
	bios->c_cc[VEOF] = lios->c_cc[LINUX_VEOF];
	bios->c_cc[VEOL] = lios->c_cc[LINUX_VEOL];
	bios->c_cc[VMIN] = lios->c_cc[LINUX_VMIN];
	bios->c_cc[VTIME] = lios->c_cc[LINUX_VTIME];
	bios->c_cc[VEOL2] = lios->c_cc[LINUX_VEOL2];
	bios->c_cc[VSUSP] = lios->c_cc[LINUX_VSUSP];
	bios->c_cc[VSTART] = lios->c_cc[LINUX_VSTART];
	bios->c_cc[VSTOP] = lios->c_cc[LINUX_VSTOP];
	bios->c_cc[VREPRINT] = lios->c_cc[LINUX_VREPRINT];
	bios->c_cc[VDISCARD] = lios->c_cc[LINUX_VDISCARD];
	bios->c_cc[VWERASE] = lios->c_cc[LINUX_VWERASE];
	bios->c_cc[VLNEXT] = lios->c_cc[LINUX_VLNEXT];

	for (i=0; i<NCCS; i++) {
		if (i != VMIN && i != VTIME &&
		    bios->c_cc[i] == LINUX_POSIX_VDISABLE)
			bios->c_cc[i] = _POSIX_VDISABLE;
	}

	bios->c_ispeed = bios->c_ospeed =
	    linux_to_bsd_speed(lios->c_cflag & LINUX_CBAUD, sptab);
}