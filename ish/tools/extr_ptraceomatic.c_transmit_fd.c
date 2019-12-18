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
struct user_regs_struct {int rsp; int rax; int rbx; int rcx; scalar_t__ rdx; } ;
struct msghdr {char* msg_control; int msg_controllen; } ;
struct cmsghdr {int /*<<< orphan*/  cmsg_len; int /*<<< orphan*/  cmsg_type; int /*<<< orphan*/  cmsg_level; } ;
typedef  int /*<<< orphan*/  sent_fd ;
typedef  int /*<<< orphan*/  msg_bak ;
typedef  int /*<<< orphan*/  msg32 ;
typedef  int /*<<< orphan*/  cmsg_bak ;
typedef  int /*<<< orphan*/  cmsg ;
typedef  int addr_t ;
struct TYPE_2__ {int real_fd; } ;

/* Variables and functions */
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 int /*<<< orphan*/  CMSG_LEN (int) ; 
 int CMSG_SPACE (int) ; 
 int /*<<< orphan*/  SCM_RIGHTS ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 TYPE_1__* f_get (int) ; 
 int /*<<< orphan*/  getregs (int,struct user_regs_struct*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pt_readn (int,int,...) ; 
 int /*<<< orphan*/  pt_writen (int,int,...) ; 
 int /*<<< orphan*/  sendmsg (int,struct msghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setregs (int,struct user_regs_struct*) ; 
 int /*<<< orphan*/  step (int) ; 
 int /*<<< orphan*/  trycall (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int transmit_fd(int pid, int sender, int receiver, int fake_fd) {
    // this sends the fd over a unix domain socket. yes, I'm crazy

    // sending part
    int real_fd = f_get(fake_fd)->real_fd;
    struct msghdr msg = {};
    char cmsg[CMSG_SPACE(sizeof(int))];
    memset(cmsg, 0, sizeof(cmsg));

    msg.msg_control = cmsg;
    msg.msg_controllen = sizeof(cmsg);

    struct cmsghdr *cmsg_hdr = CMSG_FIRSTHDR(&msg);
    cmsg_hdr->cmsg_level = SOL_SOCKET;
    cmsg_hdr->cmsg_type = SCM_RIGHTS;
    cmsg_hdr->cmsg_len = CMSG_LEN(sizeof(int));
    *(int *) CMSG_DATA(cmsg_hdr) = real_fd;

    trycall(sendmsg(sender, &msg, 0), "sendmsg insanity");

    // receiving part
    // painful, because we're 64-bit and the child is 32-bit and I want to kill myself
    struct user_regs_struct saved_regs;
    getregs(pid, &saved_regs);
    struct user_regs_struct regs = saved_regs;

    // reserve space for 32-bit version of cmsg
    regs.rsp -= 16; // according to my calculations
    addr_t cmsg_addr = regs.rsp;
    char cmsg_bak[16];
    pt_readn(pid, regs.rsp, cmsg_bak, sizeof(cmsg_bak));

    // copy 32-bit msghdr
    regs.rsp -= 32;
    int msg32[] = {0, 0, 0, 0, cmsg_addr, 20, 0};
    addr_t msg_addr = regs.rsp;
    char msg_bak[32];
    pt_readn(pid, regs.rsp, msg_bak, sizeof(msg_bak));
    pt_writen(pid, regs.rsp, &msg32, sizeof(msg32));

    regs.rax = 372;
    regs.rbx = receiver;
    regs.rcx = msg_addr;
    regs.rdx = 0;
    // assume we're already on an int $0x80
    setregs(pid, &regs);
    step(pid);
    getregs(pid, &regs);

    int sent_fd;
    if ((long) regs.rax >= 0)
        pt_readn(pid, cmsg_addr + 12, &sent_fd, sizeof(sent_fd));
    else
        sent_fd = regs.rax;

    // restore crap
    pt_writen(pid, cmsg_addr, cmsg_bak, sizeof(cmsg_bak));
    pt_writen(pid, msg_addr, msg_bak, sizeof(msg_bak));
    setregs(pid, &regs);

    if (sent_fd < 0) {
        errno = -sent_fd;
        perror("remote recvmsg insanity");
        exit(1);
    }

    return sent_fd;
}