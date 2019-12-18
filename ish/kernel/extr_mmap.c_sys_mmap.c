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
struct mmap_arg_struct {int /*<<< orphan*/  offset; int /*<<< orphan*/  fd; int /*<<< orphan*/  flags; int /*<<< orphan*/  prot; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  _EFAULT ; 
 int /*<<< orphan*/  mmap_common (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ user_get (int /*<<< orphan*/ ,struct mmap_arg_struct) ; 

addr_t sys_mmap(addr_t args_addr) {
    struct mmap_arg_struct args;
    if (user_get(args_addr, args))
        return _EFAULT;
    return mmap_common(args.addr, args.len, args.prot, args.flags, args.fd, args.offset);
}