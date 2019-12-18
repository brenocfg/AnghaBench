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
struct TYPE_2__ {int lflags; unsigned char* cc; } ;
struct tty {scalar_t__ fg_group; scalar_t__ bufsize; TYPE_1__ termios; } ;
typedef  int /*<<< orphan*/  sigset_t_ ;

/* Variables and functions */
 int ISIG_ ; 
 int NOFLSH_ ; 
 int SIGINT_ ; 
 int SIGQUIT_ ; 
 int SIGTSTP_ ; 
 size_t VINTR_ ; 
 size_t VQUIT_ ; 
 size_t VSUSP_ ; 
 int /*<<< orphan*/  sigset_add (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool tty_send_input_signal(struct tty *tty, char ch, sigset_t_ *queue) {
    if (!(tty->termios.lflags & ISIG_))
        return 0;
    unsigned char *cc = tty->termios.cc;
    int sig;
    if (ch == cc[VINTR_])
        sig = SIGINT_;
    else if (ch == cc[VQUIT_])
        sig = SIGQUIT_;
    else if (ch == cc[VSUSP_])
        sig = SIGTSTP_;
    else
        return false;

    if (tty->fg_group != 0) {
        if (!(tty->termios.lflags & NOFLSH_))
            tty->bufsize = 0;
        sigset_add(queue, sig);
    }
    return true;
}