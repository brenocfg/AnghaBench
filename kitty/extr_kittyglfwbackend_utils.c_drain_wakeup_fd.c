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
typedef  int /*<<< orphan*/  drain_buf ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 scalar_t__ read (int,char*,int) ; 

__attribute__((used)) static void
drain_wakeup_fd(int fd, int events, void* data) {
    static char drain_buf[64];
    while(read(fd, drain_buf, sizeof(drain_buf)) < 0 && errno == EINTR);
}