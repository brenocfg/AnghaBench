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
 int /*<<< orphan*/  log_cur_pos () ; 
 int /*<<< orphan*/  transaction_id ; 
 int /*<<< orphan*/  transaction_log_pos ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_transaction_begin () {
  transaction_log_pos = log_cur_pos ();
  transaction_id++;
  vkprintf (1, "Begin transaction Ox%X\n", transaction_id);
}