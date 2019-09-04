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
typedef  int /*<<< orphan*/  message ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  finish_all () ; 
 int /*<<< orphan*/  flush_binlog_last () ; 
 int /*<<< orphan*/  kwrite (int,char const*,int) ; 
 int /*<<< orphan*/  sync_binlog (int) ; 

__attribute__((used)) static void sigterm_handler (const int sig) {
  const char message[] = "SIGTERM handled.\nOnly part of dump imported\n";
  kwrite (2, message, sizeof (message) - (size_t)1);

  flush_binlog_last ();
  sync_binlog (2);
  finish_all ();
  exit (1);
}