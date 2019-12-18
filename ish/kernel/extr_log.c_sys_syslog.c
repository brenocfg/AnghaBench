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
typedef  int int_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int do_syslog (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_lock ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

int_t sys_syslog(int_t type, addr_t buf_addr, int_t len) {
    lock(&log_lock);
    int retval = do_syslog(type, buf_addr, len);
    unlock(&log_lock);
    return retval;
}