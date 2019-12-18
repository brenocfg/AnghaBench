#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct repl_server_status {int /*<<< orphan*/  session_id; scalar_t__ binlog; scalar_t__ buffer; TYPE_2__* server_next; TYPE_1__* server_prev; } ;
struct TYPE_4__ {TYPE_1__* server_prev; } ;
struct TYPE_3__ {TYPE_2__* server_next; } ;

/* Variables and functions */
 scalar_t__ active_repl_servers ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close_binlog (scalar_t__,int) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  get_server_by_session (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ) ; 

int destroy_server (struct repl_server_status *S) {
  vkprintf (1, "destroyed server %d\n", S->session_id);
  S->server_next->server_prev = S->server_prev;
  S->server_prev->server_next = S->server_next;
  if (S->buffer) {
    // will be funny if we have pending aio_read in this buffer
    free (S->buffer);
  }
  if (S->binlog) {
    close_binlog (S->binlog, 1);
  }
  get_server_by_session (S->session_id, -1);
  assert (--active_repl_servers >= 0);
  return 0;
}