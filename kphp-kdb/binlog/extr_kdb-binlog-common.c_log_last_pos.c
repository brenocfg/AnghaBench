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
 scalar_t__ binlog_disabled ; 
 long long log_cur_pos () ; 
 long long log_write_pos () ; 

long long log_last_pos (void) {
  return binlog_disabled ? log_cur_pos () : log_write_pos ();
}