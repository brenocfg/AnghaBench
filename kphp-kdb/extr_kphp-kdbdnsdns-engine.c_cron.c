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
typedef  int /*<<< orphan*/  worker_stats_t ;
struct connection {int last_query_time; scalar_t__ status; int /*<<< orphan*/  ev; int /*<<< orphan*/  fd; int /*<<< orphan*/ * type; } ;

/* Variables and functions */
 struct connection* Connections ; 
 scalar_t__ WStats ; 
 int /*<<< orphan*/  check_children_status () ; 
 scalar_t__ conn_expect_query ; 
 scalar_t__ conn_write_close ; 
 int /*<<< orphan*/  ct_dns_server ; 
 int max_connection ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int now ; 
 int /*<<< orphan*/  put_event_into_heap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  semaphore ; 
 int /*<<< orphan*/  update_idle_stats () ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ worker_id ; 
 int /*<<< orphan*/  wstat ; 

__attribute__((used)) static void cron (void) {
  static int cur_conn_idx = 0;
  int seek_steps = 100, first_conn_idx = cur_conn_idx;
  int t = now - 120;
  while (seek_steps > 0) {
    struct connection *c = Connections + cur_conn_idx;
    if (c->type == &ct_dns_server && c->last_query_time < t && c->status == conn_expect_query) {
      vkprintf (3, "Closing idle TCP connection %d.\n", c->fd);
      c->status = conn_write_close;
      put_event_into_heap (c->ev);
    }
    if (++cur_conn_idx > max_connection) {
      cur_conn_idx = 0;
    }
    if (cur_conn_idx == first_conn_idx) {
      break;
    }
    seek_steps--;
  }

  if (worker_id >= 0) {
    update_idle_stats ();
    if (!sem_wait (&semaphore)) {
      memcpy (WStats + worker_id, &wstat, sizeof (worker_stats_t));
      sem_post (&semaphore);
    }
  }
  check_children_status ();
}