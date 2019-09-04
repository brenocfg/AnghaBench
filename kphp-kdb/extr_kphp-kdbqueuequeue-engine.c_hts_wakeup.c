#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hts_data {int query_flags; TYPE_2__* extra; } ;
struct connection {scalar_t__ status; int parse_state; scalar_t__ pending_queries; scalar_t__ generation; } ;
struct TYPE_6__ {int n; TYPE_1__** k; } ;
typedef  TYPE_2__ qkey_group ;
struct TYPE_5__ {char* name; scalar_t__ lock; int /*<<< orphan*/ * conn; scalar_t__ subscribed; } ;

/* Variables and functions */
 struct hts_data* HTS_DATA (struct connection*) ; 
 int QF_KEEPALIVE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clear_connection_timeout (struct connection*) ; 
 scalar_t__ conn_expect_query ; 
 scalar_t__ conn_generation ; 
 scalar_t__ conn_wait_net ; 
 scalar_t__ conn_write_close ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* get_events_http_group (TYPE_2__*) ; 
 int http_return_history (struct connection*,char*) ; 
 int /*<<< orphan*/  qkey_group_free (TYPE_2__*) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int hts_wakeup (struct connection *c) {
//  fprintf (stderr, "HTS_WAKEUP: IN\n");
  struct hts_data *D = HTS_DATA(c);

  qkey_group *k = D->extra;

  if (verbosity > 2) {
    fprintf (stderr, "hts_wakeup : keys [");
    int i;
    for (i = 0; i < k->n; i++) {
      fprintf (stderr, "%s%c", k->k[i]->name, ",]"[i + 1 == k->n]);
    }
    fprintf (stderr, "\n");
  }

  assert (c->status == conn_expect_query || c->status == conn_wait_net);
  c->status = conn_expect_query;
  clear_connection_timeout (c);

  if (!(D->query_flags & QF_KEEPALIVE)) {
    c->status = conn_write_close;
    c->parse_state = -1;
  }

  char *ans = get_events_http_group (k);
  c->generation = ++conn_generation;
  c->pending_queries = 0;

  int i;
  for (i = 0; i < k->n; i++) {
    k->k[i]->lock--;
    k->k[i]->subscribed = 0;
    k->k[i]->conn = NULL;
    assert (k->k[i]->lock >= 0);
  }
  qkey_group_free (k);
  D->extra = NULL;

//  fprintf (stderr, "HTS_WAKEUP: OUT\n");
  return http_return_history (c, ans);
}