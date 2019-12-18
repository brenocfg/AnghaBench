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
struct connection {int /*<<< orphan*/  last_query_sent_time; int /*<<< orphan*/  Out; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct conn_target {int port; TYPE_1__ target; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* flush_query ) (struct connection*) ;} ;

/* Variables and functions */
 TYPE_2__* MCC_FUNC (struct connection*) ; 
 int /*<<< orphan*/  assert (int) ; 
 char* conv_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct connection* get_target_connection (struct conn_target*) ; 
 int my_verbosity_tmp ; 
 int /*<<< orphan*/  precise_now ; 
 struct conn_target* queue_conn ; 
 int /*<<< orphan*/  sent_queries ; 
 int sprintf (char*,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (struct connection*) ; 
 scalar_t__ verbosity ; 
 int write_out (int /*<<< orphan*/ *,char*,int) ; 

int send_to_queue (char *query, int query_len, int q_id) {
  struct conn_target *S = queue_conn;
  struct connection *d = get_target_connection (S);
  if (!d) {
    if (verbosity > 0) {
      fprintf (stderr, "cannot find connection to target %s:%d for query %s, dropping query\n", S ? conv_addr (S->target.s_addr, 0) : "?", S ? S->port : 0, query);
    }
    return -1;
  }
  if (my_verbosity_tmp > 1) {
    fprintf (stderr, "send query %d|%s\n", q_id, query);
  }

  static char header[50];
  int hn = sprintf (header, "set %d@entry 0 0 %d\r\n", q_id, query_len);

  assert (write_out (&d->Out, header, hn) == hn);
  assert (write_out (&d->Out, query, query_len) == query_len);
  assert (write_out (&d->Out, "\r\n", 2) == 2);

  sent_queries++;

  MCC_FUNC (d)->flush_query (d);
  d->last_query_sent_time = precise_now;
  return 0;
}