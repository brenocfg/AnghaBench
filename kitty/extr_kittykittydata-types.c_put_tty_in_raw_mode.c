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
struct termios {int* c_cc; } ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_SetFromErrno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_OSError ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 size_t VMIN ; 
 size_t VTIME ; 
 int /*<<< orphan*/  cfmakeraw (struct termios*) ; 
 scalar_t__ tcsetattr (int,int /*<<< orphan*/ ,struct termios*) ; 

__attribute__((used)) static inline bool
put_tty_in_raw_mode(int fd, const struct termios* termios_p, bool read_with_timeout) {
    struct termios raw_termios = *termios_p;
    cfmakeraw(&raw_termios);
    if (read_with_timeout) {
        raw_termios.c_cc[VMIN] = 0; raw_termios.c_cc[VTIME] = 1;
    } else {
        raw_termios.c_cc[VMIN] = 1; raw_termios.c_cc[VTIME] = 0;
    }
    if (tcsetattr(fd, TCSAFLUSH, &raw_termios) != 0) { PyErr_SetFromErrno(PyExc_OSError); return false; }
    return true;
}