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
struct gather_data {scalar_t__ new_key_len; int /*<<< orphan*/  new_key; } ;
struct connection {scalar_t__ generation; struct conn_query* first_query; } ;
struct conn_query {scalar_t__ req_generation; struct conn_query* next; scalar_t__ extra; struct connection* requester; } ;

/* Variables and functions */
 struct gather_data* GATHER_QUERY (struct conn_query*) ; 
 int /*<<< orphan*/  cur_key ; 
 scalar_t__ cur_key_len ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_key (char const*,int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

struct conn_query* get_conn_query (struct connection *c, const char *data, int len) {
  if (!get_key (data, len)) {
    return 0;
  }
  struct conn_query *q = c->first_query;
  while (q != (struct conn_query*)c) {
    struct connection *C = q->requester;
    if (C->generation != q->req_generation) {
      q = q->next;
      continue;
    }
    struct conn_query *Q_fake = (struct conn_query*)q->extra;
    struct conn_query *Q = C->first_query;
    while (Q != (struct conn_query*)C) {
      if (Q == Q_fake) {
        break;
      }
      Q = Q->next;
    }
    if (Q == (struct conn_query*)C) {
      q = q->next;
      continue;
    }
    struct gather_data *G = GATHER_QUERY((struct conn_query*)q->extra);
    if (G->new_key_len == cur_key_len && !memcmp (G->new_key, cur_key, cur_key_len)) {
      return q;
    }
    q = q->next;
  }
  if (verbosity) {
    fprintf (stderr, "No target gather found. Dropping request.\n");
  }
  return 0;
}