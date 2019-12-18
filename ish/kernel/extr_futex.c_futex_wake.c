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
struct futex {int /*<<< orphan*/  cond; } ;
typedef  int dword_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  TODO (char*,int) ; 
 struct futex* futex_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  futex_put (struct futex*) ; 
 int /*<<< orphan*/  notify (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_once (int /*<<< orphan*/ *) ; 

int futex_wake(addr_t uaddr, dword_t val) {
    struct futex *futex = futex_get(uaddr);
    if (val == 1)
        notify_once(&futex->cond);
    else if (val == 0x7fffffff)
        notify(&futex->cond);
    else
        TODO("invalid number of futex wakes %d", val);
    futex_put(futex);
    return val; // FIXME wrong if val is INT_MAX
}