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
struct rpc_get_file_data {int /*<<< orphan*/  out; } ;
struct rpc_forward_query {double deadline; struct rpc_forward_query* prev; struct rpc_forward_query* next; struct rpc_get_file_data* L; } ;
struct connection {int dummy; } ;

/* Variables and functions */
 struct connection* find_target_connection (struct rpc_get_file_data*) ; 
 int /*<<< orphan*/  rpc_forward_file_content (struct connection*,struct rpc_get_file_data*) ; 
 int /*<<< orphan*/  rpc_send_file_content (int /*<<< orphan*/ ,struct rpc_get_file_data*) ; 

__attribute__((used)) static int forward_query_check_completion (struct rpc_forward_query *F, double t) {
  int r = 0;
  struct rpc_get_file_data *L = F->L;
  struct connection *C = find_target_connection (L);
  if (C) {
    rpc_forward_file_content (C, L);
    r = 1;
  } else if (t >= F->deadline) {
    rpc_send_file_content (L->out, L);
    r = 1;
  }
  if (r) {
    struct rpc_forward_query *u = F->prev, *v = F->next;
    u->next = v;
    v->prev = u;
  }
  return r;
}