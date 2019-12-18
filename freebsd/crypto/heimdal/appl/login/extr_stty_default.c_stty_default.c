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
struct termios {int c_iflag; int c_lflag; int c_oflag; void** c_cc; } ;

/* Variables and functions */
 int BRKINT ; 
 void* Ctl (char) ; 
 int ECHO ; 
 int ECHOCTL ; 
 int ECHOE ; 
 int ECHOK ; 
 int ECHOKE ; 
 int ECHOPRT ; 
 int FLUSHO ; 
 int ICANON ; 
 int ICRNL ; 
 int IEXTEN ; 
 int IGNPAR ; 
 int IMAXBEL ; 
 int ISIG ; 
 int IXANY ; 
 int IXON ; 
 int ONLCR ; 
 int OPOST ; 
 int OXTABS ; 
 int /*<<< orphan*/  TCSANOW ; 
 int TOSTOP ; 
 size_t VEOF ; 
 size_t VERASE ; 
 size_t VINTR ; 
 size_t VKILL ; 
 size_t VSUSP ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 

void
stty_default(void)
{
    struct	termios termios;

    /*
     * Finalize the terminal settings. Some systems default to 8 bits,
     * others to 7, so we should leave that alone.
     */
    tcgetattr(0, &termios);

    termios.c_iflag |= (BRKINT|IGNPAR|ICRNL|IXON|IMAXBEL);
    termios.c_iflag &= ~IXANY;

    termios.c_lflag |= (ISIG|IEXTEN|ICANON|ECHO|ECHOE|ECHOK|ECHOCTL|ECHOKE);
    termios.c_lflag &= ~(ECHOPRT|TOSTOP|FLUSHO);

    termios.c_oflag |= (OPOST|ONLCR);
    termios.c_oflag &= ~OXTABS;

    termios.c_cc[VINTR] = Ctl('C');
    termios.c_cc[VERASE] = Ctl('H');
    termios.c_cc[VKILL] = Ctl('U');
    termios.c_cc[VEOF] = Ctl('D');

    termios.c_cc[VSUSP] = Ctl('Z');

    tcsetattr(0, TCSANOW, &termios);
}