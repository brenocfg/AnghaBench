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
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  F_GETPATH ; 
 scalar_t__ MAX_PATH ; 
 int fcntl (int,int /*<<< orphan*/ ,char*) ; 
 size_t readlink (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int getpath(int fd, char *buf) {
#if defined(__linux__)
    char proc_fd[20];
    sprintf(proc_fd, "/proc/self/fd/%d", fd);
    ssize_t size = readlink(proc_fd, buf, MAX_PATH - 1);
    if (size >= 0)
        buf[size] = '\0';
    return size;
#elif defined(__APPLE__)
    return fcntl(fd, F_GETPATH, buf);
#endif
}