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

/* Variables and functions */
 int /*<<< orphan*/  FIFO_OVERWRITE ; 
 scalar_t__ fifo_capacity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fifo_write (int /*<<< orphan*/ *,char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_buf ; 
 scalar_t__ log_max_since_clear ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void log_buf_append(const char *msg) {
    fifo_write(&log_buf, msg, strlen(msg), FIFO_OVERWRITE);
    log_max_since_clear += strlen(msg);
    if (log_max_since_clear > fifo_capacity(&log_buf))
        log_max_since_clear = fifo_capacity(&log_buf);
}