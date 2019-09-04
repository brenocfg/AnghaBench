#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct connection {scalar_t__ status; int generation; TYPE_4__* type; scalar_t__ flags; TYPE_3__* next; TYPE_2__* prev; struct conn_query* first_query; struct conn_target* target; } ;
struct conn_target {scalar_t__ outbound_connections; scalar_t__ min_connections; scalar_t__ next_reconnect; scalar_t__ refcnt; int /*<<< orphan*/  active_outbound_connections; } ;
struct conn_query {TYPE_1__* cq_type; } ;
struct TYPE_8__ {int (* free_buffers ) (struct connection*) ;int /*<<< orphan*/  (* crypto_free ) (struct connection*) ;} ;
struct TYPE_7__ {TYPE_2__* prev; } ;
struct TYPE_6__ {TYPE_3__* next; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* close ) (struct conn_query*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  active_outbound_connections ; 
 int /*<<< orphan*/  clear_connection_timeout (struct connection*) ; 
 int /*<<< orphan*/  compute_next_reconnect (struct conn_target*) ; 
 scalar_t__ conn_connecting ; 
 scalar_t__ conn_none ; 
 int /*<<< orphan*/  create_new_connections (struct conn_target*) ; 
 int /*<<< orphan*/  delete_conn_query (struct conn_query*) ; 
 int /*<<< orphan*/  outbound_connections ; 
 scalar_t__ precise_now ; 
 int /*<<< orphan*/  stub1 (struct conn_query*) ; 
 int /*<<< orphan*/  stub2 (struct connection*) ; 
 int stub3 (struct connection*) ; 

int client_close_connection (struct connection *c, int who) {
  struct conn_query *q;
  struct conn_target *S = c->target;

  clear_connection_timeout (c);

  if (c->first_query) {
    while (c->first_query != (struct conn_query *) c) {
      q = c->first_query;
      q->cq_type->close (q);
      if (c->first_query == q) {
        delete_conn_query (q);
      }
    }
  }

  if (c->type->crypto_free) {
    c->type->crypto_free (c);
  }

  if (S) {
    c->next->prev = c->prev;
    c->prev->next = c->next;
    --S->outbound_connections;
    --outbound_connections;
    if (c->status != conn_connecting) {
      --S->active_outbound_connections;
      --active_outbound_connections;
    }
    if (S->outbound_connections < S->min_connections && precise_now >= S->next_reconnect && S->refcnt > 0) {
      create_new_connections (S);
      if (S->next_reconnect <= precise_now) {
        compute_next_reconnect (S);
      }
    }
  }

  c->status = conn_none;
  c->flags = 0;
  c->generation = -1;

  return c->type->free_buffers(c);
}