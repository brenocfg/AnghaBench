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
typedef  int sigset_t_ ;
typedef  scalar_t__ dword_t ;
struct TYPE_2__ {int blocked; } ;

/* Variables and functions */
 scalar_t__ SIG_BLOCK_ ; 
 scalar_t__ SIG_SETMASK_ ; 
 scalar_t__ SIG_UNBLOCK_ ; 
 int _EINVAL ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  sigmask_set (int) ; 

__attribute__((used)) static int do_sigprocmask(dword_t how, sigset_t_ set) {
    if (how == SIG_BLOCK_)
        sigmask_set(current->blocked | set);
    else if (how == SIG_UNBLOCK_)
        sigmask_set(current->blocked & ~set);
    else if (how == SIG_SETMASK_)
        sigmask_set(set);
    else
        return _EINVAL;
    return 0;
}