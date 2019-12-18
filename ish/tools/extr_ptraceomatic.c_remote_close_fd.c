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
struct user_regs_struct {long rip; int rax; int rbx; } ;

/* Variables and functions */
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  getregs (int,struct user_regs_struct*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  setregs (int,struct user_regs_struct*) ; 
 int /*<<< orphan*/  step (int) ; 

__attribute__((used)) static void remote_close_fd(int pid, int fd, long int80_ip) {
    // lettuce spray
    struct user_regs_struct saved_regs;
    getregs(pid, &saved_regs);
    struct user_regs_struct regs = saved_regs;
    regs.rip = int80_ip;
    regs.rax = 6;
    regs.rbx = fd;
    setregs(pid, &regs);
    step(pid);
    getregs(pid, &regs);
    if ((long) regs.rax < 0) {
        errno = -regs.rax;
        perror("remote close fd");
        exit(1);
    }
    setregs(pid, &regs);
}