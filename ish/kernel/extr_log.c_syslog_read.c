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
 int FIFO_LAST ; 
 int _EFAULT ; 
 int _EINVAL ; 
 size_t fifo_capacity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fifo_read (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_buf ; 
 size_t log_max_since_clear ; 
 char* malloc (int) ; 
 int user_write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int syslog_read(addr_t buf_addr, int_t len, int flags) {
    if (len < 0)
        return _EINVAL;
    if (flags & FIFO_LAST) {
        if ((size_t) len > log_max_since_clear)
            len = log_max_since_clear;
    } else {
        if ((size_t) len > fifo_capacity(&log_buf))
            len = fifo_capacity(&log_buf);
    }
    char *buf = malloc(len);
    fifo_read(&log_buf, buf, len, flags);
    int fail = user_write(buf_addr, buf, len);
    free(buf);
    if (fail)
        return _EFAULT;
    return len;
}