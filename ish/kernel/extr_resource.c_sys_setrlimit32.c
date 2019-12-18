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
struct rlimit_ {int /*<<< orphan*/  max; int /*<<< orphan*/  cur; } ;
typedef  int dword_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _EFAULT ; 
 int check_setrlimit (int,struct rlimit_) ; 
 int /*<<< orphan*/  current ; 
 int rlimit_set (int /*<<< orphan*/ ,int,struct rlimit_) ; 
 scalar_t__ user_get (int /*<<< orphan*/ ,struct rlimit_) ; 

dword_t sys_setrlimit32(dword_t resource, addr_t rlim_addr) {
    struct rlimit_ rlimit;
    if (user_get(rlim_addr, rlimit))
        return _EFAULT;
    STRACE("setrlimit(%d, {cur=%#x, max=%#x})", resource, rlimit.cur, rlimit.max);
    int err = check_setrlimit(resource, rlimit);
    if (err < 0)
        return err;
    return rlimit_set(current, resource, rlimit);
}