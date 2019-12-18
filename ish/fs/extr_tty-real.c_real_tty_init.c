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
struct winsize {int /*<<< orphan*/  ws_ypixel; int /*<<< orphan*/  ws_xpixel; int /*<<< orphan*/  ws_row; int /*<<< orphan*/  ws_col; } ;
struct TYPE_2__ {int /*<<< orphan*/  ypixel; int /*<<< orphan*/  xpixel; int /*<<< orphan*/  row; int /*<<< orphan*/  col; } ;
struct tty {scalar_t__ num; int /*<<< orphan*/  thread; int /*<<< orphan*/  termios; TYPE_1__ winsize; } ;
struct termios {int c_oflag; } ;

/* Variables and functions */
 scalar_t__ ENOTTY ; 
 int /*<<< orphan*/  ERRNO_DIE (char*) ; 
 int ONLCR ; 
 int OPOST ; 
 scalar_t__ REAL_TTY_NUM ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int _EIO ; 
 int /*<<< orphan*/  cfmakeraw (struct termios*) ; 
 scalar_t__ errno ; 
 int errno_map () ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct winsize*) ; 
 struct termios old_termios ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void* (*) (void*),struct tty*) ; 
 int /*<<< orphan*/  pthread_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ real_tty_read_thread ; 
 scalar_t__ tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 scalar_t__ tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  termios_from_real (struct termios) ; 

int real_tty_init(struct tty *tty) {
    if (tty->num != REAL_TTY_NUM)
        return 0;

    struct winsize winsz;
    if (ioctl(STDIN_FILENO, TIOCGWINSZ, &winsz) < 0) {
        if (errno == ENOTTY)
            goto notty;
        return errno_map();
    }
    tty->winsize.col = winsz.ws_col;
    tty->winsize.row = winsz.ws_row;
    tty->winsize.xpixel = winsz.ws_xpixel;
    tty->winsize.ypixel = winsz.ws_ypixel;

    struct termios termios;
    if (tcgetattr(STDIN_FILENO, &termios) < 0)
        return errno_map();
    tty->termios = termios_from_real(termios);

    old_termios = termios;
    cfmakeraw(&termios);
#ifdef NO_CRLF
    termios.c_oflag |= OPOST | ONLCR;
#endif
    if (tcsetattr(STDIN_FILENO, TCSANOW, &termios) < 0)
        ERRNO_DIE("failed to set terminal to raw mode");
notty:

    if (pthread_create(&tty->thread, NULL, (void *(*)(void *)) real_tty_read_thread, tty) < 0)
        // ok if this actually happened it would be weird AF
        return _EIO;
    pthread_detach(tty->thread);
    return 0;
}