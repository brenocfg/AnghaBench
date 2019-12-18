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
struct user_regs_struct {int /*<<< orphan*/  rsp; } ;
typedef  int dword_t ;
typedef  int addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_GETREGS ; 
 scalar_t__ pt_read (int,int) ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct user_regs_struct*) ; 
 int /*<<< orphan*/  trycall (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static addr_t aux_addr(int pid, unsigned type) {
    struct user_regs_struct regs;
    trycall(ptrace(PTRACE_GETREGS, pid, NULL, &regs), "ptrace get sp for aux");
    dword_t sp = (dword_t) regs.rsp;
    // skip argc
    sp += 4;
    // skip argv
    while (pt_read(pid, sp) != 0)
        sp += 4;
    sp += 4;
    // skip envp
    while (pt_read(pid, sp) != 0)
        sp += 4;
    sp += 4;
    // dig through auxv
    dword_t aux_type;
    while ((aux_type = pt_read(pid, sp)) != 0) {
        sp += 4;
        if (aux_type == type) {
            return sp;
        }
        sp += 4;
    }
    return 0;
}