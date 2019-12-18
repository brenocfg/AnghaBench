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
struct rpc_server_collection {int num; int /*<<< orphan*/ * servers; } ;
struct rpc_connection {long long default_actor_id; double default_query_timeout; struct rpc_server_collection* servers; scalar_t__ fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_PREALLOC (int,int) ; 
 int /*<<< orphan*/  END_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (struct rpc_server_collection*) ; 
 int /*<<< orphan*/  connect ; 
 int /*<<< orphan*/  last_connection_fd ; 
 int /*<<< orphan*/  lrand48 () ; 
 int /*<<< orphan*/  rpc_connection_tree ; 
 struct rpc_server_collection* rpc_find_persistent (unsigned int,int,double,double) ; 
 scalar_t__ rpc_open (int /*<<< orphan*/ ,char**,int*) ; 
 int /*<<< orphan*/  rpc_server_new (unsigned int,int,double,double) ; 
 int /*<<< orphan*/  tree_insert_connection (int /*<<< orphan*/ ,struct rpc_connection*,int /*<<< orphan*/ ) ; 
 struct rpc_connection* zzmalloc (int) ; 
 int /*<<< orphan*/ * zzrealloc (int /*<<< orphan*/ *,int,int) ; 

struct rpc_connection *do_new_rpc_connection (unsigned host, int port, int num, long long default_actor_id, double default_query_timeout, double connect_timeout, double retry_timeout, char **error, int *errnum) { /* {{{ */
  ADD_CNT (connect);
  START_TIMER (connect);
  struct rpc_server_collection *servers = rpc_find_persistent (host, port, connect_timeout, retry_timeout);
  assert (servers);
  if (servers->num < num) {
    //fprintf (stderr, "( servers->num = %d, servers=%p, servers->servers = %p\n", servers->num, servers, servers->servers);
    servers->servers = zzrealloc (servers->servers, servers->num * sizeof (void *), num * sizeof (void *));
    //fprintf (stderr, ")");
    ADD_PREALLOC (servers->num * sizeof (void *), num * sizeof (void *));
    int i;
    for (i = servers->num; i < num; i++) {
      servers->servers[i] = rpc_server_new (host, port, default_query_timeout, retry_timeout);
    }
    servers->num = num;
  }

  int i;
  int cc = 0;
  for (i = 0; i < servers->num; i++) {
    if (rpc_open (servers->servers[i], error, errnum) >= 0) {
      cc ++;
    }
  }
  if (!cc) {
    END_TIMER (connect);
    return 0;
  }

  struct rpc_connection *c = zzmalloc (sizeof (*c));
  c->fd = last_connection_fd ++;
  c->servers = servers;
  c->default_actor_id = default_actor_id;
  c->default_query_timeout = default_query_timeout;
  rpc_connection_tree = tree_insert_connection (rpc_connection_tree, c, lrand48 ());
  END_TIMER (connect);
  return c;
}