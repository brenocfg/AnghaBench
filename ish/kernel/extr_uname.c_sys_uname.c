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
struct uname {int dummy; } ;
typedef  int /*<<< orphan*/  dword_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  _EFAULT ; 
 int /*<<< orphan*/  do_uname (struct uname*) ; 
 scalar_t__ user_put (int /*<<< orphan*/ ,struct uname) ; 

dword_t sys_uname(addr_t uts_addr) {
    struct uname uts;
    do_uname(&uts);
    if (user_put(uts_addr, uts))
        return _EFAULT;
    return 0;
}