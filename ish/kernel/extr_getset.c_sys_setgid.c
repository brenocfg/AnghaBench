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
typedef  scalar_t__ uid_t_ ;
typedef  int /*<<< orphan*/  int_t ;
struct TYPE_2__ {scalar_t__ gid; scalar_t__ sgid; scalar_t__ egid; } ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  _EPERM ; 
 TYPE_1__* current ; 
 scalar_t__ superuser () ; 

int_t sys_setgid(uid_t_ gid) {
    STRACE("setgid(%d)", gid);
    if (superuser()) {
        current->gid = current->sgid = gid;
    } else {
        if (gid != current->gid && gid != current->sgid)
            return _EPERM;
    }
    current->egid = gid;
    return 0;
}