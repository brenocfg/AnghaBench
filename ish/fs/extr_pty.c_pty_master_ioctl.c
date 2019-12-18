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
struct TYPE_2__ {int locked; int packet_mode; struct tty* other; } ;
struct tty {int num; TYPE_1__ pty; } ;
typedef  int dword_t ;

/* Variables and functions */
#define  TIOCGPKT_ 131 
#define  TIOCGPTN_ 130 
#define  TIOCPKT_ 129 
#define  TIOCSPTLCK_ 128 
 int _ENOTTY ; 

__attribute__((used)) static int pty_master_ioctl(struct tty *tty, int cmd, void *arg) {
    struct tty *slave = tty->pty.other;
    switch (cmd) {
        case TIOCSPTLCK_:
            slave->pty.locked = !!*(dword_t *) arg;
            break;
        case TIOCGPTN_:
            *(dword_t *) arg = slave->num;
            break;
        case TIOCPKT_:
            tty->pty.packet_mode = !!*(dword_t *) arg;
            break;
        case TIOCGPKT_:
            *(dword_t *) arg = tty->pty.packet_mode;
            break;
        default:
            return _ENOTTY;
    }
    return 0;
}