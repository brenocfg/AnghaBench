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
 int /*<<< orphan*/  flush_binlog_forced (int) ; 
 int /*<<< orphan*/  flush_binlog_ts () ; 
 scalar_t__ log_cur_pos () ; 
 scalar_t__ log_readto_pos ; 

void flush_binlog_last (void) {
  if (log_cur_pos () != log_readto_pos) {
    flush_binlog_ts ();
  } else {
    flush_binlog_forced (1);
  }
}