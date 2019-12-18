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
struct winsize_ {int dummy; } ;
struct termios_ {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  dword_t ;

/* Variables and functions */
#define  FIONREAD_ 142 
#define  TCFLSH_ 141 
#define  TCGETS_ 140 
#define  TCSETSF_ 139 
#define  TCSETSW_ 138 
#define  TCSETS_ 137 
#define  TIOCGPKT_ 136 
#define  TIOCGPRGP_ 135 
#define  TIOCGPTN_ 134 
#define  TIOCGWINSZ_ 133 
#define  TIOCPKT_ 132 
#define  TIOCSCTTY_ 131 
#define  TIOCSPGRP_ 130 
#define  TIOCSPTLCK_ 129 
#define  TIOCSWINSZ_ 128 

__attribute__((used)) static ssize_t tty_ioctl_size(int cmd) {
    switch (cmd) {
        case TCGETS_: case TCSETS_: case TCSETSF_: case TCSETSW_:
            return sizeof(struct termios_);
        case TIOCGWINSZ_: case TIOCSWINSZ_:
            return sizeof(struct winsize_);
        case TIOCGPRGP_: case TIOCSPGRP_:
        case TIOCSPTLCK_: case TIOCGPTN_:
        case TIOCPKT_: case TIOCGPKT_:
        case FIONREAD_:
            return sizeof(dword_t);
        case TCFLSH_: case TIOCSCTTY_:
            return 0;
    }
    return -1;
}