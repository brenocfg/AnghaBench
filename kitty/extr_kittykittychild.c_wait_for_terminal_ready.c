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

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int read (int,char*,int) ; 

__attribute__((used)) static inline void
wait_for_terminal_ready(int fd) {
    char data;
    while(1) {
        int ret = read(fd, &data, 1);
        if (ret == -1 && (errno == EINTR || errno == EAGAIN)) continue;
        break;
    }
}