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
struct rlimit32_ {scalar_t__ cur; scalar_t__ max; } ;
typedef  int dword_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 int _EFAULT ; 
 int do_getrlimit32 (int,struct rlimit32_*) ; 
 scalar_t__ user_put (int /*<<< orphan*/ ,struct rlimit32_) ; 

dword_t sys_old_getrlimit32(dword_t resource, addr_t rlim_addr) {
    struct rlimit32_ rlimit;
    int err = do_getrlimit32(resource, &rlimit);
    if (err < 0)
        return err;

    // This version of the call is for programs that aren't aware of rlim_t
    // being 64 bit. RLIM_INFINITY looks like -1 when truncated to 32 bits.
    if (rlimit.cur > INT_MAX)
        rlimit.cur = INT_MAX;
    if (rlimit.max > INT_MAX)
        rlimit.max = INT_MAX;

    if (user_put(rlim_addr, rlimit))
        return _EFAULT;
    return 0;
}