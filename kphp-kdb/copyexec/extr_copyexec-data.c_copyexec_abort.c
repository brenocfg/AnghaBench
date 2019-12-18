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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  flush_binlog_last () ; 
 scalar_t__ getpid () ; 
 scalar_t__ main_pid ; 
 int /*<<< orphan*/  sync_binlog (int) ; 

__attribute__((used)) static void copyexec_abort (void) {
  assert (main_pid == getpid ());
  flush_binlog_last ();
  sync_binlog (2);
  exit (1);
}