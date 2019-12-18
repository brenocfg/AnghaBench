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
struct TYPE_2__ {int c_iflag; int c_lflag; int /*<<< orphan*/  c_oflag; int /*<<< orphan*/  c_cflag; } ;

/* Variables and functions */
 int ECHO ; 
 int ECHOE ; 
 int ECHOK ; 
 int ICANON ; 
 int ICRNL ; 
 int INPCK ; 
 int IUCLC ; 
 int /*<<< orphan*/  OLCUC ; 
 int /*<<< orphan*/  ONLCR ; 
 int /*<<< orphan*/  OXTABS ; 
 int /*<<< orphan*/  PARENB ; 
 int PARMRK ; 
 int /*<<< orphan*/  PARODD ; 
 TYPE_1__ mode ; 
 scalar_t__ tgetflag (char*) ; 

void
set_conversions(int usingupper)
{
	if (tgetflag("UC") || usingupper) {
#ifdef IUCLC
		mode.c_iflag |= IUCLC;
		mode.c_oflag |= OLCUC;
#endif
	} else if (tgetflag("LC")) {
#ifdef IUCLC
		mode.c_iflag &= ~IUCLC;
		mode.c_oflag &= ~OLCUC;
#endif
	}
	mode.c_iflag &= ~(PARMRK | INPCK);
	mode.c_lflag |= ICANON;
	if (tgetflag("EP")) {
		mode.c_cflag |= PARENB;
		mode.c_cflag &= ~PARODD;
	}
	if (tgetflag("OP")) {
		mode.c_cflag |= PARENB;
		mode.c_cflag |= PARODD;
	}

#ifdef ONLCR
	mode.c_oflag |= ONLCR;
#endif
	mode.c_iflag |= ICRNL;
	mode.c_lflag |= ECHO;
	mode.c_oflag |= OXTABS;
	if (tgetflag("NL")) {			/* Newline, not linefeed. */
#ifdef ONLCR
		mode.c_oflag &= ~ONLCR;
#endif
		mode.c_iflag &= ~ICRNL;
	}
	if (tgetflag("HD"))			/* Half duplex. */
		mode.c_lflag &= ~ECHO;
	if (tgetflag("pt"))			/* Print tabs. */
		mode.c_oflag &= ~OXTABS;
	mode.c_lflag |= (ECHOE | ECHOK);
}