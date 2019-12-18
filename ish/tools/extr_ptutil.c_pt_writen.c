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
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open_mem (int) ; 
 int /*<<< orphan*/  trycall (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  write (int,void*,size_t) ; 

void pt_writen(int pid, addr_t addr, void *buf, size_t count) {
    int fd = open_mem(pid);
    trycall(lseek(fd, addr, SEEK_SET), "write seek");
    trycall(write(fd, buf, count), "write write");
    close(fd);
}