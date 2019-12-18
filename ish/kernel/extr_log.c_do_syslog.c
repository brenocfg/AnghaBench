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
typedef  int /*<<< orphan*/  int_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int FIFO_LAST ; 
 int FIFO_PEEK ; 
#define  SYSLOG_ACTION_CLEAR_ 138 
#define  SYSLOG_ACTION_CLOSE_ 137 
#define  SYSLOG_ACTION_CONSOLE_LEVEL_ 136 
#define  SYSLOG_ACTION_CONSOLE_OFF_ 135 
#define  SYSLOG_ACTION_CONSOLE_ON_ 134 
#define  SYSLOG_ACTION_OPEN_ 133 
#define  SYSLOG_ACTION_READ_ 132 
#define  SYSLOG_ACTION_READ_ALL_ 131 
#define  SYSLOG_ACTION_READ_CLEAR_ 130 
#define  SYSLOG_ACTION_SIZE_BUFFER_ 129 
#define  SYSLOG_ACTION_SIZE_UNREAD_ 128 
 int _EINVAL ; 
 int fifo_capacity (int /*<<< orphan*/ *) ; 
 int fifo_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_buf ; 
 int /*<<< orphan*/  log_max_since_clear ; 
 int syslog_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int do_syslog(int type, addr_t buf_addr, int_t len) {
    int res;
    switch (type) {
        case SYSLOG_ACTION_READ_:
            return syslog_read(buf_addr, len, 0);
        case SYSLOG_ACTION_READ_ALL_:
            return syslog_read(buf_addr, len, FIFO_LAST | FIFO_PEEK);

        case SYSLOG_ACTION_READ_CLEAR_:
            res = syslog_read(buf_addr, len, FIFO_LAST | FIFO_PEEK);
            if (res < 0)
                return res;
            // fallthrough
        case SYSLOG_ACTION_CLEAR_:
            log_max_since_clear = 0;
            return 0;

        case SYSLOG_ACTION_SIZE_UNREAD_:
            return fifo_size(&log_buf);
        case SYSLOG_ACTION_SIZE_BUFFER_:
            return fifo_capacity(&log_buf);

        case SYSLOG_ACTION_CLOSE_:
        case SYSLOG_ACTION_OPEN_:
        case SYSLOG_ACTION_CONSOLE_OFF_:
        case SYSLOG_ACTION_CONSOLE_ON_:
        case SYSLOG_ACTION_CONSOLE_LEVEL_:
            return 0;
        default:
            return _EINVAL;
    }
}