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
struct TYPE_2__ {int c_iflag; unsigned int c_oflag; int c_lflag; int /*<<< orphan*/  c_cflag; } ;

/* Variables and functions */
 int ECHO ; 
 int ECHOE ; 
 int ECHOK ; 
 int ICANON ; 
 int ICRNL ; 
 int INPCK ; 
 int IUCLC ; 
 unsigned int OLCUC ; 
 unsigned int ONLCR ; 
 unsigned int OXTABS ; 
 int /*<<< orphan*/  PARENB ; 
 int PARMRK ; 
 int /*<<< orphan*/  PARODD ; 
 scalar_t__ has_hardware_tabs ; 
 TYPE_1__ mode ; 
 char* newline ; 
 scalar_t__ tgetflag (char*) ; 

__attribute__((used)) static void
set_conversions(void)
{
#ifdef __OBSOLETE__
    /*
     * Conversion logic for some *really* ancient terminal glitches,
     * not supported in terminfo.  Left here for succeeding generations
     * to marvel at.
     */
    if (tgetflag("UC")) {
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
#endif /* __OBSOLETE__ */

#ifdef TERMIOS
#ifdef ONLCR
    mode.c_oflag |= ONLCR;
#endif
    mode.c_iflag |= ICRNL;
    mode.c_lflag |= ECHO;
#ifdef OXTABS
    mode.c_oflag |= OXTABS;
#endif /* OXTABS */

    /* test used to be tgetflag("NL") */
    if (newline != (char *) 0 && newline[0] == '\n' && !newline[1]) {
	/* Newline, not linefeed. */
#ifdef ONLCR
	mode.c_oflag &= ~((unsigned) ONLCR);
#endif
	mode.c_iflag &= ~((unsigned) ICRNL);
    }
#ifdef __OBSOLETE__
    if (tgetflag("HD"))		/* Half duplex. */
	mode.c_lflag &= ~ECHO;
#endif /* __OBSOLETE__ */
#ifdef OXTABS
    /* test used to be tgetflag("pt") */
    if (has_hardware_tabs)	/* Print tabs. */
	mode.c_oflag &= ~OXTABS;
#endif /* OXTABS */
    mode.c_lflag |= (ECHOE | ECHOK);
#endif
}