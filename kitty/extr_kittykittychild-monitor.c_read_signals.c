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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ EIO ; 
#define  SIGCHLD 130 
#define  SIGINT 129 
#define  SIGTERM 128 
 scalar_t__ errno ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ read (int,char*,int) ; 

__attribute__((used)) static inline void
read_signals(int fd, bool *kill_signal, bool *child_died) {
    static char buf[256];
    while(true) {
        ssize_t len = read(fd, buf, sizeof(buf));
        if (len < 0) {
            if (errno == EINTR) continue;
            if (errno != EIO) perror("Call to read() from read_signals() failed");
            break;
        }
        for (ssize_t i = 0; i < len; i++) {
            switch(buf[i]) {
                case SIGCHLD:
                    *child_died = true; break;
                case SIGINT:
                case SIGTERM:
                    *kill_signal = true; break;
                default:
                    break;
            }
        }
        break;
    }
}