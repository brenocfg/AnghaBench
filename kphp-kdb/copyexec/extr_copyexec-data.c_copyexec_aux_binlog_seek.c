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
 int /*<<< orphan*/  aux_log_read_start ; 
 int /*<<< orphan*/  aux_log_readto_pos ; 
 int /*<<< orphan*/  get_aux_binlog_jump_log_pos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transactions ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void copyexec_aux_binlog_seek (void) {
  get_aux_binlog_jump_log_pos (&aux_log_read_start);
  vkprintf (3, "after get_aux_binlog_jump_log_pos: aux_log_readto_start = %lld, transactions = %d\n", aux_log_read_start, transactions);
  aux_log_readto_pos = aux_log_read_start;
}