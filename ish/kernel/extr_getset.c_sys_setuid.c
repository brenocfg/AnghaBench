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
struct TYPE_2__ {scalar_t__ uid; scalar_t__ suid; scalar_t__ euid; } ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  _EPERM ; 
 TYPE_1__* current ; 
 scalar_t__ superuser () ; 

int_t sys_setuid(uid_t_ uid) {
    STRACE("setuid(%d)", uid);
    if (superuser()) {
        current->uid = current->suid = uid;
    } else {
        if (uid != current->uid && uid != current->suid)
            return _EPERM;
    }
    current->euid = uid;
    return 0;
}