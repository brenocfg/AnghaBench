#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sfd; } ;
typedef  TYPE_1__ engine_t ;

/* Variables and functions */
 int SIGINT ; 
 int SIGTERM ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  epoll_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_binlog_last () ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 int pending_signals ; 
 int /*<<< orphan*/  sync_binlog (int) ; 

void server_exit (engine_t *E) {
  epoll_close (E->sfd);
  close (E->sfd);
  flush_binlog_last ();
  sync_binlog (2);
  if (pending_signals & (1 << SIGTERM)) {
    kprintf ("Terminated by SIGTERM.\n");
  } else if (pending_signals & (1 << SIGINT)) {
    kprintf ("Terminated by SIGINT.\n");
  }
}