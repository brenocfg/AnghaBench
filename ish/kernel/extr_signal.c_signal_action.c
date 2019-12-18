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
struct sighand {struct sigaction_* action; } ;
struct sigaction_ {scalar_t__ handler; } ;

/* Variables and functions */
#define  SIGCHLD_ 136 
#define  SIGCONT_ 135 
#define  SIGIO_ 134 
 int SIGNAL_CALL_HANDLER ; 
 int SIGNAL_IGNORE ; 
 int SIGNAL_KILL ; 
 int SIGNAL_STOP ; 
#define  SIGSTOP_ 133 
#define  SIGTSTP_ 132 
#define  SIGTTIN_ 131 
#define  SIGTTOU_ 130 
#define  SIGURG_ 129 
#define  SIGWINCH_ 128 
 scalar_t__ SIG_DFL_ ; 
 scalar_t__ SIG_IGN_ ; 
 scalar_t__ signal_is_blockable (int) ; 

__attribute__((used)) static int signal_action(struct sighand *sighand, int sig) {
    if (signal_is_blockable(sig)) {
        struct sigaction_ *action = &sighand->action[sig];
        if (action->handler == SIG_IGN_)
            return SIGNAL_IGNORE;
        if (action->handler != SIG_DFL_)
            return SIGNAL_CALL_HANDLER;
    }

    switch (sig) {
        case SIGURG_: case SIGCONT_: case SIGCHLD_:
        case SIGIO_: case SIGWINCH_:
            return SIGNAL_IGNORE;

        case SIGSTOP_: case SIGTSTP_: case SIGTTIN_: case SIGTTOU_:
            return SIGNAL_STOP;

        default:
            return SIGNAL_KILL;
    }
}