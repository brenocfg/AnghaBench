#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rusage_ {int dummy; } ;
typedef  int dword_t ;
typedef  int /*<<< orphan*/  addr_t ;
struct TYPE_4__ {TYPE_1__* group; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; struct rusage_ children_rusage; } ;

/* Variables and functions */
#define  RUSAGE_CHILDREN_ 129 
#define  RUSAGE_SELF_ 128 
 int _EFAULT ; 
 int _EINVAL ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 struct rusage_ rusage_get_current () ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ user_put (int /*<<< orphan*/ ,struct rusage_) ; 

dword_t sys_getrusage(dword_t who, addr_t rusage_addr) {
    struct rusage_ rusage;
    switch (who) {
        case RUSAGE_SELF_:
            rusage = rusage_get_current();
            break;
        case RUSAGE_CHILDREN_:
            lock(&current->group->lock);
            rusage = current->group->children_rusage;
            unlock(&current->group->lock);
            break;
        default:
            return _EINVAL;
    }
    if (user_put(rusage_addr, rusage))
        return _EFAULT;
    return 0;
}