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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int O_DIRECTORY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  SYS_getdents64 ; 
 int open (char*,int) ; 
 int syscall (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

int main() {
    int fd = open(".", O_RDONLY | O_DIRECTORY);
    char buf[100];
    int count = syscall(SYS_getdents64, fd, buf, sizeof(buf));
    write(STDOUT_FILENO, buf, count);
}