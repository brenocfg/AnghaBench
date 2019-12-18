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
struct dl_phdr_info {int dummy; } ;
typedef  int /*<<< orphan*/  RtldLockState ;
typedef  int /*<<< orphan*/  Obj_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  _rtld_error (char*) ; 
 int /*<<< orphan*/  lock_release (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obj_from_addr (void const*) ; 
 int /*<<< orphan*/  rlock_acquire (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtld_bind_lock ; 
 int /*<<< orphan*/  rtld_fill_dl_phdr_info (int /*<<< orphan*/  const*,struct dl_phdr_info*) ; 

int
_rtld_addr_phdr(const void *addr, struct dl_phdr_info *phdr_info)
{
    const Obj_Entry *obj;
    RtldLockState lockstate;

    rlock_acquire(rtld_bind_lock, &lockstate);
    obj = obj_from_addr(addr);
    if (obj == NULL) {
        _rtld_error("No shared object contains address");
	lock_release(rtld_bind_lock, &lockstate);
        return (0);
    }
    rtld_fill_dl_phdr_info(obj, phdr_info);
    lock_release(rtld_bind_lock, &lockstate);
    return (1);
}