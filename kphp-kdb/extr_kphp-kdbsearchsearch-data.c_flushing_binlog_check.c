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
 int ULOG_BUFFER_SIZE ; 
 int compute_uncommitted_log_bytes () ; 
 int /*<<< orphan*/  flush_binlog_forced (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void flushing_binlog_check (void) {
  if (compute_uncommitted_log_bytes () > ((ULOG_BUFFER_SIZE) >> 1)) {
    flush_binlog_forced (0);
  }
}